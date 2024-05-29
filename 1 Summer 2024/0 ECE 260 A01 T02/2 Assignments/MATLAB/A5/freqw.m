function [freqresp, omega] = freqw(ncoefs, dcoefs, omega)
    % Evaluate the frequency response of H(ω) at given ω points
    freqresp = polyval(ncoefs, omega) ./ polyval(dcoefs, omega);
    
    % If no output arguments were specified, plot the frequency response
    if nargout == 0
        % Compute the magnitude and phase responses
        magresp = abs(freqresp);
        phaseresp = angle(freqresp);
        
        % Plot the magnitude response
        subplot(2, 1, 1);
        plot(omega, magresp);
        title('Magnitude Response');
        xlabel('Frequency (rad/s)');
        ylabel('Magnitude (unitless)');
        
        % Plot the phase response
        subplot(2, 1, 2);
        plot(omega, phaseresp);
        title('Phase Response');
        xlabel('Frequency (rad/s)');
        ylabel('Angle (rad)');
    end
end


