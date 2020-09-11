#include<iostream>
#include<list>
#include<ctime>
#include<windows.h>

using namespace std;

class Exchange;

class Cryptocurrency
{
protected:

	string Coin_name;
	int price_coin;
	bool trend;


public:


	void Raising_prices(int price)
	{
		price_coin += price;
	}
	
	void Price_reduction(int price)
	{
		price_coin -= price;
	}
	bool Get_Trend()
	{
		return trend;
	}
	void Set_Trend(bool trend)
	{
		this->trend = trend;
	}
	int Get_Prise()
	{
		return price_coin;
	}


};

class Bitcoin : public Cryptocurrency
{
public:
	Bitcoin()
	{
		this->Coin_name = "Bitcoin";
		this->price_coin = 5000;
	}
};

class Ethereum : public Cryptocurrency
{
public:
	Ethereum()
	{
		this->Coin_name = "Ethereum";
		this->price_coin = 1000;
	}
};

class XRP : public Cryptocurrency
{
public:
	XRP()
	{
		this->Coin_name = "XRP";
		this->price_coin = 500;
	}
};

class Bitcoin_Cash : public Cryptocurrency
{
public:
	Bitcoin_Cash()
	{
		this->Coin_name = "Bitcoin Cash";
		this->price_coin = 900;
	}
};

class Litecoin : public Cryptocurrency
{
public:
	Litecoin()
	{
		this->Coin_name = "Litecoin";
		this->price_coin = 200;
	}
};


class Buyer
{
public:

	virtual void Update(Exchange*) = 0;
};


class Exchange
{
private:

	Bitcoin bitcoin;
	Ethereum ethereum;
	XRP  xrp;
	Bitcoin_Cash bitcoin_Cash;
	Litecoin litecoin;
	list<Buyer*> buyers;

public:


	void Attach(Buyer* pBuyer)
	{
		buyers.push_back(pBuyer);
	}
	void Detach(Buyer* pBuyer)
	{
		for (auto it = buyers.begin(); it != buyers.end(); it++)
		{
			if (*it == pBuyer)
			{
				buyers.erase(it);
				return;
			}
		}
	}
	void Notify()
	{
		for (auto it = buyers.begin(); it != buyers.end(); it++)
		{
			(*it)->Update(this);
		}
		cout << "\n";
	}

	void SetPrice()
	{
		int rnd;

		rnd = rand() % 2;

			if (rnd == 1)
			{
				bitcoin.Price_reduction(10);
				bitcoin.Set_Trend(false);
				ethereum.Price_reduction(10);
				ethereum.Set_Trend(false);
				xrp.Price_reduction(10);
				xrp.Set_Trend(false);
				bitcoin_Cash.Price_reduction(10);
				bitcoin_Cash.Set_Trend(false);
				litecoin.Price_reduction(10);
				litecoin.Set_Trend(false);
			}
			else
			{
				bitcoin.Raising_prices(10);
				bitcoin.Set_Trend(true);
				ethereum.Raising_prices(10);
				ethereum.Set_Trend(true);
				xrp.Raising_prices(10);
				xrp.Set_Trend(true);
				bitcoin_Cash.Raising_prices(10);
				bitcoin_Cash.Set_Trend(true);
				litecoin.Raising_prices(10);
				litecoin.Set_Trend(true);
			}
		

		Notify();
		
	}

	bool Get_status_bitcoin()
	{
		return bitcoin.Get_Trend();
	}

	bool Get_status_Ethereum()
	{
		return ethereum.Get_Trend();
	}

	bool Get_status_XRP()
	{
		return xrp.Get_Trend();
	}

	bool Get_status_bitcoin_Cash()
	{
		return bitcoin_Cash.Get_Trend();
	}

	bool Get_status_litecoin()
	{
		return litecoin.Get_Trend();
	}

	int Get_prise_bitcoin()
	{
		return bitcoin.Get_Prise();
	}

	int Get_prise_Ethereum()
	{
		return ethereum.Get_Prise();
	}

	int Get_prise_XRP()
	{
		return xrp.Get_Prise();
	}

	int Get_prise_bitcoin_Cash()
	{
		return bitcoin_Cash.Get_Prise();
	}

	int Get_prise_litecoin()
	{
		return litecoin.Get_Prise();
	}
	
};


class UkrainianBuyer : public Buyer
{
private:
	Exchange* ptr;
	string name;
	int money=100000;
public:
	UkrainianBuyer(string pName )
	{
		name = pName;
	}

	void Update(Exchange* pProduct)
	{
		if (pProduct->Get_status_bitcoin())
		{
			money -=pProduct->Get_prise_bitcoin();
		}
		else
		{
			money += pProduct->Get_prise_bitcoin();
		}

		if (pProduct->Get_status_bitcoin_Cash())
		{
			money -= pProduct->Get_prise_bitcoin_Cash();
		}
		else
		{
			money += pProduct->Get_prise_bitcoin_Cash();
		}

		if (pProduct->Get_status_Ethereum())
		{
			money -= pProduct->Get_prise_Ethereum();
		}
		else
		{
			money += pProduct->Get_prise_Ethereum();
		}

		if (pProduct->Get_status_litecoin())
		{
			money -= pProduct->Get_prise_litecoin();
		}
		else
		{
			money += pProduct->Get_prise_litecoin();
		}

		if (pProduct->Get_status_XRP())
		{
			money -= pProduct->Get_prise_XRP();
		}
		else
		{
			money += pProduct->Get_prise_XRP();
		}
	}

	void Show_money()
	{
		cout << "Money:" << money << endl;
	}
};





int main()
{
	srand(time(NULL));
	
	Exchange exchange;
	UkrainianBuyer* Buyer1 = new UkrainianBuyer("Vasa");
	exchange.Attach(Buyer1);
	

	while (true)//imitation of trade
	{
		exchange.SetPrice();
		Buyer1->Show_money();
		Sleep(1000);
		system("cls");
	}


    system("pause");
	return 0;
}