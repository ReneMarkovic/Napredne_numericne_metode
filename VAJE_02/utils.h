double gasdev() {//Generates numbers follo
	static bool available = false;
	static double gset;
	double fac, rsq, v1, v2;
	if (!available) {
		do {
			v1 = 2.0 * rand() / double(RAND_MAX) - 1.0;
			v2 = 2.0 * rand() / double(RAND_MAX) - 1.0;
			rsq = v1 * v1 + v2 * v2;
		} while (rsq >= 1.0 || rsq == 0.0);
		fac = sqrt(-2.0 * log(rsq) / rsq);
		gset = v1 * fac;
		available = true;
		return v2 * fac;
	}
	else {
		available = false;
		return gset;
	}
}

double abs_velocity(int i) {//The squer of the velocity vector
	double vSqdSum = 0;
	for (int ij = 0; ij < 3; ij++) {
		vSqdSum += v[i][ij] * v[i][ij];
	}
	return vSqdSum;
}

void initialize() {
	//inicializacija leg
	int n = int(ceil(pow(N, 1.0 / 3.0)));//stevilo delcev v posameznih smereh (x,y, in z)
	double a = L / (n);                 //distance between 2 particles
	int p = 0;                         //counter
    FILE*data;
    data = fopen("init_pos.txt","w+");
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int z = 0; z < n; z++) {
				if (p < N) {
					r[p][0] = (x + 0.5) * a;
					r[p][1] = (y + 0.5) * a;
					r[p][2] = (z + 0.5) * a;
                    fprintf(data,"%.4f\t%.4f\t%.4f\n",r[p][0],r[p][1],r[p][2]);
				}
				++p;
			}
		}
	}
    fclose(data);
	// initialize velocities
	for (int p = 0; p < N; p++) {
		for (int i = 0; i < 3; i++) {
			v[p][i] = gasdev();// vMax * (2 * rand() / double(RAND_MAX) - 1);
		}
	}
}

void final_position() {
	//inicializacija leg
	int n = int(ceil(pow(N, 1.0 / 3.0)));//stevilo delcev v posameznih smereh (x,y, in z)
    int p=0;
    FILE*data;
    data = fopen("final_pos.txt","w+");
	for (int x = 0; x < n; x++) {
		for (int y = 0; y < n; y++) {
			for (int z = 0; z < n; z++) {
				if (p < N) {
                    fprintf(data,"%.4f\t%.4f\t%.4f\n",r[p][0],r[p][1],r[p][2]);
				}
				++p;
			}
		}
	}
    fclose(data);
}

void computeAccelerations() {
	//postavimo vrednosti pospeskov a 0
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 3; k++) {
			a[i][k] = 0;
		}
	}

	//zanka preko vseh parov
	for (int i = 0; i < N ; i++) {
		for (int j = i + 1; j < N; j++) {
			double rij[3];
			double rSqd = 0;
			for (int k = 0; k < 3; k++) {
				rij[k] = r[i][k] - r[j][k];
				if (abs(rij[k]) > 0.5*L) { //Periodični robni pogoji
					if (rij[k]>0) rij[k] -= L;
					else rij[k] += L;
				}
				rSqd += rij[k] * rij[k];
			}
			double f = 24 * (2 * pow(rSqd, -7) - pow(rSqd, -4));
			for (int k = 0; k < 3; k++) {
				a[i][k] += rij[k] * f;
				a[j][k] -= rij[k] * f;
			}
		}
		for (int k = 0; k < 3; k++) {
			if (r[i][k] > L) r[i][k] -= L;
			if (r[i][k] < 0) r[i][k] += L;
		}

	}
}

void velocityVerlet(double dt) {//Integration dynamics
	computeAccelerations();
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 3; k++) {
			r[i][k] += v[i][k] * dt + 0.5 * a[i][k] * dt * dt;
			v[i][k] += 0.5 * a[i][k] * dt;
		}
	}
	computeAccelerations();
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 3; k++) {
			v[i][k] += 0.5 * a[i][k] * dt;
		}
	}
}

void skaliranje_hitrosti(double T) {
    double vSqdSum = 0.0;
    double v_cm[3] = {0.0, 0.0, 0.0};
    
    // Določimo povprčeno itrost sistema oz. hitrost masnega središča
    for (int n = 0; n < N; n++) {
        for (int i = 0; i < 3; i++) {
            v_cm[i] += v[n][i];
        }
    }
    
    for (int i = 0; i < 3; i++) {
        v_cm[i] /= N;
    }
    
    /*
	Ker želimo da velja zakon o ohranitvi gibalne količine napravimo korekcijo
	vrednosti hitrosti centriramo okoli hitrosti masnega središča
	*/
    for (int n = 0; n < N; n++) {
        for (int i = 0; i < 3; i++) {
            v[n][i] -= v_cm[i]; // Remove CM motion
            vSqdSum += v[n][i] * v[n][i];
        }
    }
    
    // SEdaj pa skaliramo hitrosti glede na temperaturo
    double lambda = sqrt(3 * (N - 1) * T / vSqdSum);
    for (int n = 0; n < N; n++) {
        for (int i = 0; i < 3; i++) {
            v[n][i] *= lambda;
        }
    }
}

double instantaneousTemperature() {//Compute the instant temperature
	double sum = 0;
	for (int i = 0; i < N; i++) {
		for (int k = 0; k < 3; k++) {
			sum += v[i][k] * v[i][k];
		}
	}
	return sum / (3 * (N - 1));
}

string ustvari_filename(int argc, char* argv[], double T, string base_name){
	// Pretvorim T v string
	ostringstream t_ss;
	t_ss << T; 
	string t_str = t_ss.str();

	size_t pos = t_str.find('.');
	//string::npos -> če ni ničle v stringu t_str (torej ni decimalne vejice)
	while (pos != string::npos) {
		t_str.replace(pos, 1, "dp"); // zamenjaj decimalno vejico z "dp", 1 znak
		pos = t_str.find('.', pos + 2); // premakni se čez novo vstavljen "dp"
	}

	string filename_str = ".\\RESULTS\\" + t_str + "_T_" + base_name + ".txt";
	char filename[50];
	strcpy(filename, filename_str.c_str());
	FILE* pisi = fopen(filename, "w+");
	fclose(pisi);
	return filename;
}

double* sorted_dist(const double r[N][3], int particle) {
    // Allocate and initialize distances array
    double* distances = new double[N];
    for (int i = 0; i < N; i++) {
        distances[i] = 0.0;
        for (int j = 0; j < 3; j++) {
            double diff = r[particle][j] - r[i][j];
            distances[i] += diff * diff;
        }
    }
    
    // Copy distances to sorted_array
    double* sorted_array = new double[N];
    for (int i = 0; i < N; i++) {
        sorted_array[i] = distances[i];
    }
    
    // Manual selection sort
    for (int i = 0; i < N - 1; i++) {
        int min_index = i;
        for (int j = i + 1; j < N; j++) {
            if (sorted_array[j] < sorted_array[min_index]) {
                min_index = j;
            }
        }
        std::swap(sorted_array[i], sorted_array[min_index]);
    }
    
    delete[] distances;
    return sorted_array; //Pazi. Prva vrednost je 0, ke rot je razdalja do samega sebe.
}

double avrage_min_nn_distance(double r[N][3], int nn){
	/*
	int nn - parameter, ki pove. koliko najbljizjih sosedov bomo upostevali
	pri določevanju povprečne najkrajše razdalje.
	*/
	double r_min_sum = 0;
	for (int i = 0; i < N; i++) {
		double* sorted_array = sorted_dist(r, i);
		for (int j = 1; j <= nn; j++) {
			r_min_sum += sqrt(sorted_array[j]);
		}
		delete[] sorted_array;
	}
	return r_min_sum / (N * nn);
}