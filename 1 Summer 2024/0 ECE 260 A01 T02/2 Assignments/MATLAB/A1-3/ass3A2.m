function ass3A2(n, theta)
    % Convert degrees to radian, and Initialize variables
    t = deg2rad(theta);
    p = [0; 0];  
    x = p.';     

    % Create a rotation matrix
    R = [cos(t), sin(t); -sin(t), cos(t)];
    x = zeros(n, 2);
    for i = 1:n
        p = p + R^(i - 1) * [i; 0];
        x(i, :) = p.';
    end

    % Plot the points
    plot(x(:, 1), x(:, 2));
    axis equal; 
    filename = sprintf('data/Ass3A2_%d_%d.ps', theta, n);
    print('-dps', filename);
end
