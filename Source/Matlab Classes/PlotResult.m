classdef PlotResult
    %PLOT Summary of this class goes here
    %   Detailed explanation goes here
    
    properties (Constant)
        %fileSuffix_RandomProcess = [{'_QUADRATIC_'},{'_UNIFORM_'}, {'_CUBIC_'}, {'_MAXIMUM_'}, {'_OPTIMAL_'}];
        fileSuffix_RandomProcess = transpose(textread('../../Release/config.txt', '%s', 'delimiter', '\n'));
        fileSuffix_Names = [{'CEM'},{'CET'},{'CMT'},{'EMT'},{'overall'},{'sparseTransition_Prepared3'},{'sparseTransition_Prepared4'},{'sparseTransition_Prepared5'},{'sparseTransition_Prepared6'}];
        filePrefix = [{'Weights'},{'Entropies'}];
        fileStatus = [{'Provided'}, {'Simulated'}];
        iterations = 1000;
    end
    methods (Static)
        function plotVector(filePrefix, fileSuffix_name, fileSuffix_RandomProcess, fileStatus, suffix)
            name = strcat(fileSuffix_name, fileSuffix_RandomProcess, suffix);
            filename = sprintf('../../Output/%s/%s/%s.txt', fileStatus, filePrefix, name);
            try
                fprintf('Plotting %s\n', filename);
                file = textread(filename, '%f', 'delimiter', '\t');
            catch exception
                if (~exist(filename, 'file'))
                    fprintf('%s does not exist\n', filename);
                    return
                else
                    rethrow(exception)
                end
            end

            result = zeros(size(file));
            if (strcmpi(filePrefix, 'Entropies'))
                for i = 1 :length(file)
                  result(i) = min(file(1 : i));
                end
            elseif (strcmpi(filePrefix,'Weights'))
                for i = 1 : length(file)
                    result(i) = sum(file(1:i));
                end
            end

            current = PlotResult.config(name); %create a figure with configuration
            plot(result);
            if (strcmpi(filePrefix, 'Entropies'))
                set(gca, 'XTick', 0:PlotResult.iterations/20:PlotResult.iterations);
                s = sprintf('Entropy for %d iterations',PlotResult.iterations);
                title(s);
                ylabel('Entropy');
            elseif (strcmpi(filePrefix,'Weights'))
               %Find y value corresponding to x = 8
                vq = interp1(result, 8);
                %Draw a vertical line to the point
                line([8 8], [0 vq(1)], 'Color', 'r', 'LineStyle', '--');
                line([0 8], [vq(1) vq(1)], 'Color', 'r','LineStyle', '--');
                quote = sprintf('(%d, %.2f)', 8, vq(1));
                text(8.1, vq(1), quote);
                s = sprintf('Probabilities of BNs');
                title(s);
                ylabel('Probabilities');
            end
            PlotResult.saveFiles(current, name, filePrefix);
        end
        
        function saveFiles(current, name, prefix)
            savePath = fullfile('../../Output', 'Graphs', prefix, strcat(name,'.eps'));
            saveas(current, savePath);
        end
        
        function current = config(name)
            current = figure('Visible','off');
            set(gcf,'numbertitle','off','name',name);
        end

        function plotAll()
            for i = 1 : length(PlotResult.fileSuffix_Names)
                for j = 1 : length(PlotResult.fileSuffix_RandomProcess)
                    for k = 1 : length(PlotResult.fileStatus)
                        PlotResult.plotVector('Entropies',PlotResult.fileSuffix_Names{i}, PlotResult.fileSuffix_RandomProcess{j}, PlotResult.fileStatus{k}, '');
                        PlotResult.plotVector('Weights',PlotResult.fileSuffix_Names{i}, PlotResult.fileSuffix_RandomProcess{j}, PlotResult.fileStatus{k}, '');
                    end
                end
            end
        end
    end   
end

