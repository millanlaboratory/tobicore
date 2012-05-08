clear all;

addpath('/usr/share/tobicore/tobicoremat/mextobicore')
addpath('/usr/share/tobicore/tobicoremat/mextobiic')
addpath('/usr/share/tobicore/tobicoremat/mextobiid')
addpath('/usr/share/tobicore/tobicoremat/mextobiplatform')

[code, desc] = tp_retval();

message = icmessage_new();
serializer = icserializerrapid_new(message);

[server] = tpic_new();

while(tpic_plug(client, '0.0.0.0', '8000', 0) ~= 1)
	disp('Cannot plug yet...');
	pause(1);
end
	
while(true)
	retval = tpic_getrapid(server, serializer);
	if(retval > 1)
		disp('Error while getting...');
		break;
	end

	buffer = icmessage_serialize(serializer);
	disp(buffer);
end
tpic_unplug(server);
