void removeOdds(vector<int>& v)
{
	for (auto i = v.begin(); i != v.end(); i++)
	{
		if (*i % 2 == 1)
		{
			i = v.erase(i); //calling the erase function invalidates our iterator. That means we have to set the iterator equal to the returned value of erase each time it's called
			i--;
		}
	}
}