void listAll(const Domain* d, string path) // two-parameter overload
{
	if (path == "")
		path = d->label() + path;
	else if (path != d->label())
		path = d->label() + "." + path;

	if (d->subdomains().empty())
	{
		cout << path;
		cout << endl;
		return;
	}
	else
	{
		for (auto i = d->subdomains().begin(); i != d->subdomains().end(); i++)
		{
			listAll(*i, path);
		}
	}
}