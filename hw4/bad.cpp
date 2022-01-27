void removeBad(list<Movie*>& li)
{
	for (auto i = li.begin(); i != li.end(); i++)
	{
		auto mp = *i;
		if (mp->rating() < 55)
		{
			i = li.erase(i);
			i--;
			delete mp;
		}
	}
}