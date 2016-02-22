struct records
{
	double dates;
	double burnedAcres;
	double months[12];
	records *next;
};


/*class records
{
public:
	double* dates;
	double* burnedAcres;
	double** months;

	records(int entrySize);
	~records();

};

records::records(int entrySize)
{
	dates = new double[entrySize];
	
	burnedAcres = new double[entrySize];
	
	months = new double*[entrySize];
	for(int i = 0; i < entrySize; ++i)
			months[i] = new double[12];

}

records::~records()
{
	delete dates;

	delete burnedAcres;

	for(int i = 0; i < 12; ++i)
		delete months[i];
	delete months;

}
*/