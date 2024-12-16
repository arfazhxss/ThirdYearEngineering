% ***** Bode diagram *****
num = [0 10 4 10];
den = [1 0.8 9 0];
bode(num, den)
title('Bode Diagram of G(s) = 10(s^2 + 0.4s + 1)/[s(s^2 + 0.8s + 9)]')