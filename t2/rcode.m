T0 = 0;
T1 = 0.0001;
V = 0;

global f;
f = 10000;

[t, vout] = ode45(@rc, [T0, T1],V);
v_s = sin(f * 2 * pi .* t)

figure(1)
plot(t, v_s);
title("Vin and Vout (10kHz)")
xlabel("Time (s)")
ylabel("Voltage (V)")
hold on
plot(t, vout);
hold off

function dv = rc(t, v)
    R = 1590;
    C = 0.1 * power(10, -6);
    global f;
    rot_v = f * 2 * pi;
    dv = (sin(rot_v * t) - v) / (R * C);
end