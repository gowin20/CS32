class Medium
{
public:
	Medium(string id) : m_id(id) {}
	virtual ~Medium() {}	
	virtual string connect() const = 0;
	virtual string transmit(string msg) const { return "text: " + msg; }
	string id() const { return m_id; }
private:
	string m_id;
};

class Phone : public Medium
{
public:
	Phone(string num, CallType type) : Medium(num) { m_type = type; }
	~Phone() { cout << "Destroying the phone " << id() << "." << endl; }
	string connect() const { return "Call"; }
	string transmit(string msg)  const
	{
		switch (m_type)
		{
		case VOICE:
			return "voice: " + msg;
		case TEXT:
			return "text: " + msg;
		}
	}
private:
	CallType m_type;
};

class TwitterAccount : public Medium
{
public:
	TwitterAccount(string id) : Medium(id) {}
	~TwitterAccount() { cout << "Destroying the Twitter account " << id() << "." << endl; }
	string connect() const { return "Tweet"; }
};

class EmailAccount : public Medium
{
public:
	EmailAccount(string id) : Medium(id) {}
	~EmailAccount() { cout << "Destroying the email account " << id() << "." << endl; }
	string connect() const { return "Email"; }
};
