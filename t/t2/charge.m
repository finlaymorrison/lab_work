R = 1590;
C = 0.1e-6;

%x = dsolve("Dx= -(1/(R*C))*x + (1/(R*C))", "x(0) = 0");
x = dsolve("Dx/Dt= sin(100t) - x/(R*C)", "x(0) = 0");

t = 0:10^(-5):10^(-3);

vout = eval(vectorize(x));

figure(1)
plot(t, vout);
title("Capacitor Voltage in an RC charging circuit");
xlabel("Time (s)");
ylabel("Voltage (V)");