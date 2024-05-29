function x = unitStepFunction2(t)
    x = zeros(size(t));
    m = length(x); 
    for i = 1 : m
        if t(i) >= 0 
            x(i) = 1;
        end 
    end
end