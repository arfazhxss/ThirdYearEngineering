fprintf('%-8s %-8s %-8s\n', 'Celsius', 'Fahrenheit', 'Kelvin'); 
for celsius = -50 : 10 : 50
    fahrenheit = 9 / 5 * celsius + 32;
    kelvin = celsius + 273.15;
    fprintf('%8.2f %8.2f %8.2f\n', celsius, fahrenheit, kelvin);
end