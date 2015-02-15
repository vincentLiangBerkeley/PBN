function plotAll()
%PLOTALL Summary of this function goes here
%   Plot all results stored in PlotResult.m
for i = 1 : length(PlotResult.fileSuffix_RandomProcess)
    for j = 1 :length(PlotResult.fileSuffix_Names)
        Ename = strcat(PlotResult.filePrefix{2},PlotResult.fileSuffix_RandomProcess{i}, PlotResult.fileSuffix_Names{j});
        fprintf('Plotting %s...', Ename);
        PlotResult.plotEntropy(Ename);
        Wname = strcat(PlotResult.filePrefix{1},PlotResult.fileSuffix_RandomProcess{i}, PlotResult.fileSuffix_Names{j});
        PlotResult.plotWeights(Wname);
    end
end

end

