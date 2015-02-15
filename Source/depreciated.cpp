
void Iterator::dynamicIterate(){
	setType(MAXIMUM);
	double entropy = iterateOnce();
	int N = boolNetworks.size();
	tMatrix input = *transition;
	vector<rMatrix> OptimalBNs;
	vector<double> OptimalQs;
	int layer = 1;
	chrono::high_resolution_clock::time_point begin = chrono::high_resolution_clock::now();
	dynamicIterateHelper(input, OptimalBNs, OptimalQs,  N, entropy, layer);
	chrono::high_resolution_clock::time_point end = chrono::high_resolution_clock::now();
	chrono::microseconds ticks = chrono::duration_cast<chrono::microseconds>(end - begin);
	elapsedTime = (double)ticks.count() / 1000000;
	cout << "Elapsed time is: " << elapsedTime << endl;


	// Codes to determine the minimum entropy
	// int min = minIndex(entropies);
	// boolNetworks = BNs[min];
	// weights = qs[min];
	// saveResult();
}

void Iterator::dynamicIterateHelper(tMatrix& input, vector<rMatrix>& OptimalBNs, vector<double>& OptimalQs, const int& N, const double& e, int& layer){
	//cout << OptimalBNs.size() << " " << N << endl;
	if(layer == 1) cout << "We are in layer 1" << endl;
	if (input.module() <= LIMIT){
		cout << "Find one decomposition!" << endl;
		exit(1);
		BNs.push_back(OptimalBNs);
		qs.push_back(OptimalQs);
		entropies.push_back(calculateEntropy(OptimalQs));
		return;
	}
	if (OptimalBNs.size() >= N) return;
	if (calculateEntropy(OptimalQs) >= e){
		//cout << "Condition not met in layer " << layer << " difference between entropies is " << calculateEntropy(OptimalQs) - e << endl;
		return;
	} 	
	priority_queue<double> maximums;
	// Initialize the priority queue
	for (int i = 0; i < (int) input.getSize(); ++i){
		map<int, double> column = input.get(i);
		int row = chooseEntry(column, MAXIMUM);
		maximums.push(-column[row]);
	}
	// Get the minimax
	double miniMax = - maximums.top();

	// We temporarily assume that the greedy-algorithm is correct
	setType(MAXIMUM);
	this->transition = new tMatrix(input);
	iterateOnce();
	if (OptimalBNs.size() + boolNetworks.size() > N){
		cout << "Greedy algorithm gives us " << boolNetworks.size() << " BNs" << endl;
		cout << "Inferior to greedy algorithm, stopped earlier at layer "<< layer << "!" << endl;
		return;
	}

	set<double> weightsChosenForThisLayer;
	// Iterate through every entry that is less than minimax
	for (int i = 0; i < (int) input.getSize(); ++i){
		map<int, double> column = input.get(i);
		// Choose the entry, explore, and un-choose
		if (column.empty()){
			//cout << "Column " << i << " is empty" << endl;
			break;
		}
		//cout << "Current col is " << i << endl;
		for(map<int, double>::iterator it_i = column.begin(); it_i != column.end(); ++it_i){
			//cout << "Current row is " << it_i->first << endl;

			// This is a possible candidate : < miniMax and not chosen
			if (it_i->second < miniMax && weightsChosenForThisLayer.find(it_i->second) == weightsChosenForThisLayer.end()){ 

				cout << "Choosing row " << it_i->first << " col " << i << " with weight " << it_i->second << " in layer " << layer << endl;
				cout << "Current input matrix is " << endl;
				input.print(cout);

				OptimalQs.push_back(it_i->second); // Choose
				weightsChosenForThisLayer.insert(it_i->second); // Put this entry into chosenEntries

				// Construct a BN corresponding to the chosen weight
				vector<int> rows; // The rows for non-zero entries
				for (int j = 0; j < (int) input.getSize(); ++j){
					map<int, double> target = input.get(j);
					double closest = 1.00;
					int chosenRow;
					for(map<int, double>::iterator it_j = target.begin(); it_j != target.end(); ++ it_j){
						if (it_j->second >= it_i->second - 0.001 && (it_j->second - it_i->second < closest)){
							closest = it_j->second - it_i->second;
							chosenRow = it_j->first;
						}
					}
					rows.push_back(chosenRow);
				}
				rMatrix A = rMatrix(rows);
				OptimalBNs.push_back(A);
				input += tMatrix::times(A, -it_i->second);

				//cout << "Matrix after subtraction is " << endl;
				//input.print(cout);

				// Explore
				layer ++;
				dynamicIterateHelper(input, OptimalBNs, OptimalQs, N, e, layer);
				layer --;
				//cout << "Ready to backtrack to layer " << layer << endl;
				// Un-Choose
				// cout << "Boolean matrix is " << endl;
				// A.print(cout);
				// cout << "Multiplying weight " << it_i->second << " is :" << endl;
				// tMatrix::times(A, it_i->second).print(cout);


				input += tMatrix::times(A, it_i->second);
				OptimalBNs.pop_back();
				OptimalQs.pop_back();
			}
		}
	}
}
