clear all;

addpath('/usr/share/tobicore/tobicoremat/mextobicore')
addpath('/usr/share/tobicore/tobicoremat/mextobiic')
addpath('/usr/share/tobicore/tobicoremat/mextobiid')
addpath('/usr/share/tobicore/tobicoremat/mextobiplatform')

[code, desc] = tp_retval();

message = icmessage_new();
serializer = icserializerrapid_new(message);

icmessage_addclassifier(message, ...
	'cnbi_mi', 'CNBI MI Classifier', ...
	icmessage_getvaluetype('prob'), icmessage_getlabeltype('biosig'));
icmessage_addclass(message, 'cnbi_mi', '0x300', 0.60);
icmessage_addclass(message, 'cnbi_mi', '0x301', 0.40);
icmessage_dumpmessage(message);
buffer = icmessage_serialize(serializer);

client = tpic_new();
while(tpic_plug(client, '127.0.0.1', '8000', 1) ~= 1)
	disp('Cannot plug yet...');
	pause(1);
end

for i = 1:100
	icmessage_setbidx(message, i);
	retval = tpic_setrapid(client,  serializer);
	if(retval > 1)
		disp('Error while setting...');
		break;
	end
	pause(1/64);
end
tpic_unplug(client);
