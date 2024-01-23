#ifndef CAPPUCCINO
#define CAPPUCCINO
#include<bits/stdc++.h>
#include"ingredient.h"
class Cappuccino : public Cinnamon
{
public:
    Cappuccino();
    Cappuccino(const Cappuccino& cap);
	~Cappuccino();
    void operator=(const Cappuccino& cap);

    virtual std::string get_name() {return this->name;}
    virtual double price() {return (this->units * this->price_unit);}

    void add_side_item(Ingredient* side);
    std::vector<Ingredient*>& get_side_items() {return side_items;}

private:
    std::vector<Ingredient*> side_items;

};
#endif // CAPPUCCINO