% Define the numerator and denominator coefficients of the transfer function
tfnum = [0 0 0 0 1];
tfdenom = [1.0000 2.6131 3.4142 2.6131 1.0000];

% Define the final simulation time
finaltime = 20;

% Create the transfer function system
sys = tf(tfnum, tfdenom);

% Plot the step response
subplot(2, 1, 1); % Create a subplot with 2 rows, 1 column, at position 1
step(sys, finaltime); % Plot the step response
title('Step Response'); % Add a title to the subplot
xlabel('Time (seconds)'); % Label the x-axis
ylabel('Amplitude'); % Label the y-axis
grid on; % Turn on the grid for better readability

% Plot the impulse response
subplot(2, 1, 2); % Create a subplot at position 2
impulse(sys, finaltime); % Plot the impulse response
title('Impulse Response'); % Add a title to the subplot
xlabel('Time (seconds)'); % Label the x-axis
ylabel('Amplitude'); % Label the y-axis
grid on; % Turn on the grid for better readability
