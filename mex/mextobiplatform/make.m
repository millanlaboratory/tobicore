% 2011-06-04  Michele Tavella <michele.tavella@epfl.ch>
disp('Building MEX interface');
try 
	mex tobiplatform.cc ../../src/tobiplatform/.libs/libtobiplatform.dll.a ../../src/tobiic/.libs/libtobiic.dll.a ../../src/tobiid/.libs/libtobiid.dll.a ../../src/tobicore/.libs/libtobicore.dll.a -I../../../src/
	exit;
catch e
	disp('Error: cannot compile');
end
