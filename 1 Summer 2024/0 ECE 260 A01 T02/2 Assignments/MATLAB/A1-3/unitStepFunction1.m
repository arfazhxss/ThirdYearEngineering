function x = unitStepFunction1(t)
    % unitstep - Compute the unit-step function.
    if t >= 0 
        x = 1;
    else
        x = 0;
    end
end

