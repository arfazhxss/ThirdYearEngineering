% Clear all variables and close all figures.
clear all;
close all;

% Define the time variable.
t = linspace(-1, 1, 1000);

% Values for n.
n_values = [1, 5, 10, 50, 100];

for n = n_values
    % Symbolic expression for the square wave.
    syms k w;
    f = symsum(0.5 * mysinc(pi * k / 2) * exp(j * k * w * t), 'k', -n, n);
    f = subs(f, w, 2 * pi);
    
    % Plot the result.
    figure;
    plot(t, real(f), 'LineWidth', 1.5);
    title(['x_{', num2str(n), '}(t)']);
    xlabel('Time');
    ylabel('Amplitude');
    grid on;
    
    % Save the plot to a file.
    print(['data/sqrwav_', num2str(n)], '-depsc');
    
end

function y = mysinc(x)
    y = ones(size(x));
    i = find(x);
    y(i) = sin(x(i)) ./ x(i);
end
