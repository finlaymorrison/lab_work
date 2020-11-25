timespan = [0 10];
v_start = 2;
R = 100e3;
C = 100e-6;

[t, v] = ode23(@(t, v) capacitor_rc(v, R, C), timespan, v_start);
i = v./R;
p = i.*v;

figure(1);
subplot(2, 2, 1);
plot(t, v, "-o"); title("Voltage"); xlabel("time (s)"); ylabel("Voltage (V)")
subplot(2, 2, 2);
plot(t, i, "-o"); title("Current"); xlabel("time (s)"); ylabel("Current (A)")
subplot(2, 2, 3);
plot(t, p, "-o"); title("Power"); xlabel("time (s)"); ylabel("Power (W)");

function dv_dt = capacitor_rc(v, R, C)
    dv_dt = -v/(R * C);
end