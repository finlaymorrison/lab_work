T0 = 0;
T1 = 0.005;
V = 0;

global f;
f = 200;

[t, vout] = ode23(@rc, [T0, T1],V);
v_s = sign(sin(f * 2 * pi .* t));

figure(1)
plot(t, v_s);
hold on
title("Vin and Vout (200Hz square wave)")
xlabel("Time (s)")
ylabel("Voltage (V)")
plot(t, vout);
hold off

function dv = rc(t, v)
    R = 1590;
    C = 0.1 * power(10, -6);
    global f;
    rot_v = f * 2 * pi;
    dv = (sign(sin(rot_v * t)) - v) / (R * C);
end