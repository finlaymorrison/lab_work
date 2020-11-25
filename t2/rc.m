frequencies = 0:1000:100000;
r = 1.59e3;
c = 0.1e-6;

magnitude = 1 ./ sqrt(1 + power(frequencies * 2 * pi * r * c, 2));
phase = -atan(r * c * frequencies * 2 * pi);

figure(1)
subplot(2,2,1)
plot(frequencies, magnitude);
title("Magnitude");
xlabel("Frequency (Hz)");
ylabel("Magnitude / Vin")
subplot(2,2,2)
plot(frequencies, phase);
title("Phase");
xlabel("Frequency (Hz)");
ylabel("Phase (Rad)")