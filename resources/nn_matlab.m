load matlab_digitpatternt.txt
load matlab_digittargets.txt
P = matlab_digitpatternt';
T = matlab_digittargets';
net = newff(P,T,20);
net = train(net,P,T);
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;0;1;1;0;1;1;0;1;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [0;1;1;1;1;1;0;0;1;0;0;1;0;0;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;0;0;1;0;1;1;1;1;0;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;0;1;1;1;1;1;0;0;1;0;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;0;1;1;1;1;1;1;1;0;0;1;0;0;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;1;0;1;1;1;0;0;1;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;1;0;1;1;1;0;0;1;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;0;0;1;0;0;1;1;1;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;0;1;1;1;1;0;1;1;0;1;0;0]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;1;1;1;1;1;1;0;1;1;1;1]);
Y
[Y, Pf, Af, E, perf] = sim(net, [1;1;1;1;1;1;1;1;1;0;0;1;0;0;1]);
Y
