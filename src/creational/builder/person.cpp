//
// Created by YangLinzhuo on 2023/12/29.
//

#include <common.h>

class PersonBuilder;
class PersonAddressBuilder;
class PersonJobBuilder;


class Person
{
// address
    std::string street_address, post_code, city;
// employment
    std::string company_name, position;
    int annual_income = 0;
    Person() = default;

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;

public:
    static PersonBuilder create();
};


class PersonBuilderBase
{
protected:
    Person& person;
    explicit PersonBuilderBase(Person& person)
            : person{person} {}
public:
    explicit operator Person()
    {
        return std::move(person);
    }
    // builder facets
    [[nodiscard]] PersonAddressBuilder lives() const;
    [[nodiscard]] PersonJobBuilder works() const;
};


class PersonBuilder : public PersonBuilderBase
{
    Person p; // object being built
public:
    PersonBuilder() : PersonBuilderBase{p} {}
};


class PersonAddressBuilder: public PersonBuilderBase
{
    typedef PersonAddressBuilder self;
public:
    explicit PersonAddressBuilder(Person& person)
            : PersonBuilderBase{ person } {}
    self& at(std::string street_address)
    {
        person.street_address = std::move(street_address);
        return *this;
    }
    self& with_postcode(std::string post_code) {
        person.post_code = std::move(post_code);
        return *this;
    }
    self& in(std::string city) {
        person.city = std::move(city);
        return *this;
    }
};

class PersonJobBuilder: public PersonBuilderBase {
    typedef PersonJobBuilder self;
public:
    explicit PersonJobBuilder(Person& person)
            : PersonBuilderBase{person} {}

    self& at(std::string company_name) {
        person.company_name = std::move(company_name);
        return *this;
    }

    self& as_a(std::string position) {
        person.position = std::move(position);
        return *this;
    }

    self& earning(int annual_income) {
        person.annual_income = annual_income;
        return *this;
    }
};


PersonAddressBuilder PersonBuilderBase::lives() const
{
    return PersonAddressBuilder{ person };
}

PersonJobBuilder PersonBuilderBase::works() const
{
    return PersonJobBuilder{ person };
}

PersonBuilder Person::create()
{
    return PersonBuilder{};
}


int main()
{
    Person p = static_cast<Person>(
            Person::create()
                    .lives().at("123 London Road")
                    .with_postcode("SW1 1GB")
                    .in("London")
                    .works().at("PragmaSoft")
                    .as_a("Consultant")
                    .earning(10e6)
    );
    return 0;
}
