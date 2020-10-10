#include <conio.h>
#include "Store.h"

void Store::browseArtists()
{
    int choice;
    do
    {
        cout<<"Artists available:"<<endl;
        showArtists();
        cout<<"[0] Back"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>choice;
        if (choice != 0)
        {
            int ch;
            do
            {
                artists[choice-1].showAlbums();
                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
                    int c;
                    cout<<"Title: "<<artists[choice-1].getAlbum(ch-1).getTitle()<<endl
                        <<"Format: "<<artists[choice-1].getAlbum(ch-1).getFormat()<<endl
                        <<"Genre: "<<artists[choice-1].getAlbum(ch-1).getGenre()<<endl
                        <<"Date: "<<artists[choice-1].getAlbum(ch-1).getDate()<<endl;
                    cout<<"Choose option: "<<endl<<"[1] Add to shopping cart"<<endl<<"[2] Add to wishlist"<<endl<<"[3] Read review"<<endl<<"[4] Write review"<<endl<<"[5] Rate album"<<endl<<"[0] Back"<<endl;
                    cin>>c;
                    switch(c)
                    {
                    case 1:
                        if (customerIn.addToCart(artists[choice-1].getName(), artists[choice-1].getAlbum(ch-1)))
                            cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" added to cart"<<endl;
                        else
                            cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" is already in your shopping cart"<<endl;
                        break;
                    case 2:
                        if (customerIn.addToWishlist(artists[choice-1].getName(), artists[choice-1].getAlbum(ch-1)))
                            cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" added to wishlist"<<endl;
                        else
                            cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" is already in your wishlist"<<endl;
                        break;
                    case 3:
                        if (!artists[choice-1].getAlbum(ch-1).getReviewed())
                            cout<<"Album does not have a review yet"<<endl;
                        else
                            cout<<artists[choice-1].getAlbum(ch-1).getReview()<<endl;
                        break;
                    case 4:
                        if (artists[choice-1].getAlbum(ch-1).getReviewed())
                            cout<<"Album already has a review"<<endl;
                        else
                        {
                            string proper, review;
                            cout<<"Write your review here: "<<endl;
                            cin.ignore();
                            getline(cin, review);
                            proper = '\n' + review;
                            addReview(choice-1, ch-1, proper);
                            writeReviews();
                            cout<<"Your review was added"<<endl;
                        }
                        break;
                    case 5:
                        if (artists[choice-1].getAlbum(ch-1).getRating() != -1)
                            cout<<"Album already has a rating of "<<artists[choice-1].getAlbum(ch-1).getRating()<<endl;
                        else
                        {
                            int rating;
                            cout<<"Enter your rating: "<<endl;
                            cin>>rating;
                            addRating(choice-1, ch-1, rating);
                            writeRatings();
                            cout<<"Your rating was added"<<endl;
                        }
                        break;
                    case 0:
                        break;
                    }
                    writeUserFiles();
                }
            }
            while (ch != 0);
        }
    }
    while (choice != 0);
}

void Store::manageCart()
{
    int choice = 0;
    if (customerIn.sizeCart() != 0)
    {
        do
        {
            cout<<"Your shopping cart contains: "<<endl;
            for (int i=0; i<customerIn.sizeCart(); i++)
                cout<<"["<<i+1<<"] "<<customerIn.getCart(i).getName()<<endl;
            cout<<"[0] Back"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
            if (choice != 0)
            {
                int ch;
                if (customerIn.sizeCart() == 0)
                    break;
                cout<<"Choose album to remove from cart: "<<endl;
                for (int i=0; i<customerIn.getCart(choice-1).getNoAlbums(); i++)
                    cout<<"["<<i+1<<"] "<<customerIn.getCart(choice-1).getAlbum(i).getTitle()<<endl;
                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
                    string name = customerIn.getCart(choice-1).getName();
                    string title = customerIn.getCart(choice-1).getAlbum(ch-1).getTitle();
                    customerIn.removeFromCart(name, title);
                    writeUserFiles();
                }
            }
        }
        while (choice != 0);
    }
    else
        cout<<"Your shopping cart is empty"<<endl;
}

void Store::manageWishlist()
{
    int choice = 0;
    if (customerIn.sizeWishlist() != 0)
    {
        do
        {
            cout<<"Your wishlist cart contains: "<<endl;
            for (int i=0; i<customerIn.sizeWishlist(); i++)
                cout<<"["<<i+1<<"] "<<customerIn.getWishlist(i).getName()<<endl;
            cout<<"[0] Back"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
            if (choice != 0)
            {
                int ch;
                if (customerIn.sizeWishlist() == 0)
                    break;
                cout<<"Choose album to remove from wishlist: "<<endl;
                for (int i=0; i<customerIn.getWishlist(choice-1).getNoAlbums(); i++)
                    cout<<"["<<i+1<<"] "<<customerIn.getWishlist(choice-1).getAlbum(i).getTitle()<<endl;
                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
                    string name = customerIn.getWishlist(choice-1).getName();
                    string title = customerIn.getWishlist(choice-1).getAlbum(ch-1).getTitle();
                    customerIn.removeFromWishlist(name, title);
                    writeUserFiles();
                }
            }
        }
        while (choice != 0);
    }
    else
        cout<<"Your wishlist is empty"<<endl;
}

void Store::browse()
{
    int choice;
    do
    {
        cout<<"Choose option: "<<endl<<"[1] Browse available artists"<<endl<<"[2] Manage shopping cart"<<endl<<"[3] Manage wishlist"<<endl<<"[0] Back"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            browseArtists();
            break;
        case 2:
            manageCart();
            break;
        case 3:
            manageWishlist();
            break;
        case 0:
            return;
        }
    }
    while (choice != 0);
}

void Store::showArtists()
{
    for (int i = 0; i < artists.size(); i++)
        cout<<"["<<i+1<<"] "<<artists[i].getName()<<endl;
}

Customer Store::findCustomer(string user)
{
    for (ic = customers.begin(); ic != customers.end(); ic++)
        if (ic->getUser() == user)
            return *ic;
    return customers.back();
}

Manager Store::findManager(string user)
{
    for (im = managers.begin(); im != managers.end(); im++ )
        if (im->getUser() == user)
            return *im;
    return managers.back();
}

void Store::populate()
{
    ifstream f("customers.txt");
    while (f)
    {
        string user, pass;
        string check = user;
        f >> user;
        if (check == user)
            break;
        f >> pass;
        addCustomer(user, pass);
    }
    f.close();
    ifstream m("managers.txt");
    while (m)
    {
        string user, pass;
        string check = user;
        m >> user;
        if (check == user)
            break;
        m >> pass;
        addManager(user, pass);
    }
}

void Store::readUserFiles()
{
    string name, title;
    string path = customerIn.getUser() + "wishlist.txt";
    ifstream a(path);
    while (a)
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            break;
        for (int i=0; i < artists.size(); i++)
        {
            if (artists[i].getName() == name)
            {
                for (int j=0; j < artists[i].getNoAlbums(); j++)
                    if (artists[i].getAlbum(j).getTitle() == title)
                        customerIn.addToWishlist(artists[i].getName(), artists[i].getAlbum(j));
            }
        }
    }
    path = customerIn.getUser() + "cart.txt";
    ifstream b(path);
    while (b)
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            break;
        for (int i=0; i < artists.size(); i++)
        {
            if (artists[i].getName() == name)
            {
                for (int j=0; j < artists[i].getNoAlbums(); j++)
                    if (artists[i].getAlbum(j).getTitle() == title)
                        customerIn.addToCart(artists[i].getName(), artists[i].getAlbum(j));
            }
        }
    }
}

void Store::writeUserFiles()
{
    string path = customerIn.getUser() + "wishlist.txt";
    ofstream a(path, ios::trunc);
    for (int i=0; i<customerIn.sizeWishlist(); i++)
    {
        for (int j=0; j<customerIn.getWishlist(i).getNoAlbums(); j++)
        {
            a << endl << customerIn.getWishlist(i).getName() << endl;
            a << customerIn.getWishlist(i).getAlbum(j).getTitle();
        }
    }
    path = customerIn.getUser() + "cart.txt";
    ofstream b(path, ios::trunc);
    for (int i=0; i<customerIn.sizeCart(); i++)
    {
        for (int j=0; j<customerIn.getCart(i).getNoAlbums(); j++)
        {
            b << endl << customerIn.getCart(i).getName() << endl;
            b << customerIn.getCart(i).getAlbum(j).getTitle();
        }
    }
}

void Store::readFiles()
{
    string name, title, format, genre;
    int date, amount;
    ifstream a("albums.txt");
    while (a)
    {
        bool existing = false;
        Album temp;
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            break;
        getline(a, format);
        getline(a, genre);
        a >> date;
        a >> amount;
        temp.setTitle(title);
        temp.setFormat(format);
        temp.setGenre(genre);
        temp.setDate(date);
        temp.setInventory(amount);
        for (int i=0; i < artists.size(); i++)
        {
            if (artists[i].getName() == name)
            {
                artists[i].addAlbum(temp);
                existing = true;
            }
        }
        if (!existing)
        {
            Artist poser;
            poser.setName(name);
            poser.addAlbum(temp);
            artists.push_back(poser);
        }
    }
}

void Store::writeFiles()
{
    ofstream a("albums.txt", ios::trunc);
    for (int i=0; i<artists.size(); i++)
    {
        for (int j=0; j<artists[i].getNoAlbums(); j++)
        {
            a << endl << artists[i].getName() << endl;
            a << artists[i].getAlbum(j).getTitle() << endl;
            a << artists[i].getAlbum(j).getFormat() << endl;
            a << artists[i].getAlbum(j).getGenre() << endl;
            a << artists[i].getAlbum(j).getDate() << endl;
            a << artists[i].getAlbum(j).getInventory();
        }
    }
}

void Store::readOrders()
{
    ifstream o("orders.txt");
    string customer, name, title;
    while (o)
    {
        string check = customer;
        getline(o, customer);   //reads newline and discards it
        getline(o, customer);
        if (customer == check)
            break;
        ifstream a(customer + "order.txt");
        Order temp;
        temp.setBuyer(customer);
        if (a)
        {
            getline(a, name);               //reads newline and discards it
            getline(a, name);
        }
        Artist poser;
        poser.setName(name);
        while (a)
        {
            getline(a, title);              //reads newline and discards it
            getline(a, title);
            for (int i=0; i < artists.size(); i++)
            {
                if (artists[i].getName() == name)
                {
                    for (int j=0; j < artists[i].getNoAlbums(); j++)
                    {
                        if (artists[i].getAlbum(j).getTitle() == title)
                        {
                            poser.addAlbum(artists[i].getAlbum(j));
                            break;
                        }
                    }
                }
            }
        }
        temp.addArtist(poser);
    }
}

void Store::writeOrders()
{
    ofstream o("orders.txt", ios::trunc);
    for (int i=0; i<orders.size(); i++)
    {
        o << endl << orders[i].getBuyer();
        ofstream a(orders[i].getBuyer() + "order.txt");
        for (int j=0; j<orders[i].getNumArtists(); j++)
        {
            a << endl << orders[i].getArtist(j).getName();
            for (int k=0; k<orders[i].getArtist(j).getNoAlbums(); k++)
            {
                a << endl << orders[i].getArtist(j).getAlbum(k).getTitle();
            }
        }
    }
}

void Store::checkout()
{
    bool existing = false;
    int pos;
    for (int i=0; i<orders.size(); i++)
    {
        if (orders[i].getBuyer() == customerIn.getUser())
        {
            existing = true;
            pos = i;
            break;
        }
    }
    if (existing)
    {
        for (int i=0; i<customerIn.sizeCart(); i++)
        {
            orders[pos].addArtist(customerIn.getCart(i));
        }
    }
    else
    {
        Order temp;
        temp.setBuyer(customerIn.getUser());
        for (int i=0; i<customerIn.sizeCart(); i++)
            temp.addArtist(customerIn.getCart(i));
        orders.push_back(temp);
    }
}

void Store::addReview(int i, int j, string review)
{
    Album edit = artists[i].getAlbum(j);
    artists[i].removeAlbum(j);
    edit.setReview(review);
    edit.setReviewed(true);
    artists[i].addAlbum(edit);
}

void Store::readReviews()
{
    string name, title;
    ifstream a("reviews.txt");
    while (a)
    {
        string temp, review;
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            break;
        getline(a, temp);
        while (temp != "<review-end>")
        {
            review = review + '\n' + temp;
            getline(a, temp);
        }
        for (int i=0; i < artists.size(); i++)
        {
            if (artists[i].getName() == name)
            {
                for (int j=0; j < artists[i].getNoAlbums(); j++)
                {
                    if (artists[i].getAlbum(j).getTitle() == title)
                        addReview(i, j, review);
                }
            }
        }
    }
}

void Store::writeReviews()
{
    ofstream a("reviews.txt", ios::trunc);
    for (int i=0; i<artists.size(); i++)
    {
        for (int j=0; j<artists[i].getNoAlbums(); j++)
        {
            if (artists[i].getAlbum(j).getReviewed())
            {
                a << endl << artists[i].getName() << endl;
                a << artists[i].getAlbum(j).getTitle();
                a << artists[i].getAlbum(j).getReview() << endl;
                a << "<review-end>" << endl;
            }
        }
    }
}

void Store::addRating(int i, int j, int rating)
{
    Album edit = artists[i].getAlbum(j);
    artists[i].removeAlbum(j);
    edit.setRating(rating);
    artists[i].addAlbum(edit);
}

void Store::readRatings()
{
    string name, title;
    int rating;
    ifstream a("ratings.txt");
    while (a)
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            break;
        a >> rating;
        for (int i=0; i < artists.size(); i++)
        {
            if (artists[i].getName() == name)
            {
                for (int j=0; j < artists[i].getNoAlbums(); j++)
                {
                    if (artists[i].getAlbum(j).getTitle() == title)
                        addRating(i, j, rating);
                }
            }
        }
    }
}

void Store::writeRatings()
{
    ofstream a("ratings.txt", ios::trunc);
    for (int i=0; i<artists.size(); i++)
    {
        for (int j=0; j<artists[i].getNoAlbums(); j++)
        {
            if (artists[i].getAlbum(j).getRating() != -1)
            {
                a << endl << artists[i].getName() << endl;
                a << artists[i].getAlbum(j).getTitle() << endl;
                a << artists[i].getAlbum(j).getRating();
            }
        }
    }
}

void Store::addManager(string user, string pass)
{
    Manager temp;
    temp.setUser(user);
    temp.setPass(pass);
    managers.push_back(temp);
}

void Store::addCustomer(string user, string pass)
{
    Customer temp;
    temp.setUser(user);
    temp.setPass(pass);
    customers.push_back(temp);
}

void Store::mLogin()
{
    string user, pass;
    cout<<"User name: "<<endl;
    cin.ignore();
    getline(cin, user);
    Manager temp = findManager(user);
    if (temp.getUser() != user)
    {
        cout<<"User name not found. Try again"<<endl;
        return;
    }
    cout<<"Password: "<<endl;
    getline(cin, pass);
    if (temp.getPass() == pass)
    {
        cout<<"Welcome, "<<user<<endl;
        managerIn = temp;
        accessLevel = 2;
    }
    else
    {
        cout<<"Password does not match user. Try again"<<endl;
        return;
    }
}

void Store::cLogin()
{
    string user, pass;
    cout<<"User name: "<<endl;
    cin.ignore();
    getline(cin, user);
    Customer temp = findCustomer(user);
    if (temp.getUser() != user)
    {
        cout<<"User name not found. Try again"<<endl;
        return;
    }
    cout<<"Password: "<<endl;
    getline(cin, pass);
    if (temp.getPass() == pass)
    {
        cout<<"Welcome, "<<user<<endl;
        customerIn = temp;
        accessLevel = 1;
        readUserFiles();
    }
    else
    {
        cout<<"Password does not match user. Try again"<<endl;
        return;
    }
}

void Store::cReg()
{
    string user, pass;
    cout<<"Desired user name: "<<endl;
    cin.ignore();
    getline(cin, user);
    if (findCustomer(user).getUser() == user)
    {
        cout<<"User name already taken. Please choose a different one"<<endl;
        return;
    }
    cout<<"Desired password: "<<endl;
    getline(cin, pass);
    ofstream of ("customers.txt", ios::app);
    of << endl << user << " " << pass;
    of.close();
    cout<<"Account created successfully. You have been automatically logged in"<<endl;
    addCustomer (user, pass);
    accessLevel = 1;
    customerIn = customers.back();
}

void Store::mainPage()
{
    populate();
    readOrders();
    readFiles();
    readReviews();
    readRatings();
    while (accessLevel != -1)
    {
        switch(accessLevel)
        {
        case 0:
            guestPage();
            break;
        case 1:
            customerPage();
            break;
        case 2:
            managerPage();
            break;
        }
    }
    cout<<"Now leaving the store"<<endl;
    _getch();
}

void Store::guestPage()
{
    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Customer Login"<<endl<<"[2] Customer Register"<<endl<<"[3] Manager Login"<<endl<<"[0] Exit"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        cLogin();
        break;
    case 2:
        cReg();
        break;
    case 3:
        mLogin();
        break;
    case 0:
        accessLevel = -1;
        return;
    }
}

void Store::loggedIn()
{
    cout<<"Logged in as: ";
    switch (accessLevel)
    {
    case 0:
        cout<<"[Guest]"<<endl;
        break;
    case 1:
        cout<<customerIn.getUser()<<" [Customer]"<<endl;
        break;
    case 2:
        cout<<managerIn.getUser()<<" [Manager]"<<endl;
        break;
    }
}

void Store::customerPage()
{
    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Browse"<<endl<<"[2] Checkout"<<endl<<"[0] Logout"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        browse();
        break;
    case 2:
        checkout();
        writeOrders();
        cout<<"The contents of your shopping cart have been ordered "<<endl;
        break;
    case 0:
        accessLevel = 0;
        break;
    }
}

void Store::managerPage()
{
    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Manage open orders"<<endl<<"[2] Manage store"<<endl<<"[0] Logout"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        break;
    case 2:
        manageStore();
        break;
    case 0:
        accessLevel = 0;
        break;
    }
}

void Store::manageStore()
{
    int choice;
    cout<<"Choose option: "<<endl<<"[1] Add artist"<<endl<<"[2] Manage artist"<<endl<<"[0] Back"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        addArtist();
        break;
    case 2:
        manageArtist();
        break;
    case 0:
        break;
    }
}

void Store::manageArtist()
{
    int choice, ch;
    cout<<"Choose artist to manage: "<<endl;
    for (int i=0; i < artists.size(); i++)
        cout<<"["<<i+1<<"] "<<artists[i].getName()<<endl;
    cin>>choice;
    choice--;
    cout<<"Managing artist "<<artists[choice].getName()<<endl;
    cout<<"Choose option: "<<endl<<"[1] Remove artist"<<endl<<"[2] Edit artist"<<endl<<"[3] Add album"<<endl<<"[4] Manage album"<<endl<<"[0] Back"<<endl;
    cin>>ch;
    switch(ch)
    {
    case 1:
        cout<<"Artist "<<artists[choice].getName()<<" Removed"<<endl;
        artists.erase(artists.begin()+choice);
        break;
    case 2:
        editArtist(choice);
        break;
    case 3:
        addAlbum(choice);
        break;
    case 4:
        manageAlbum(choice);
        break;
    case 0:
        break;
    }
    writeFiles();
}

void Store::manageAlbum(int choice)
{
    int ch, c;
    cout<<"Choose album to manage"<<endl;
    for (int i=0; i < artists[choice].getNoAlbums(); i++)
        cout<<"["<<i+1<<"] "<<artists[choice].getAlbum(i).getTitle()<<endl;
    cin>>ch;
    ch--;
    cout<<"Managing album "<<artists[choice].getAlbum(ch).getTitle()<<" by "<<artists[choice].getName()<<endl;
    cout<<"Choose option: "<<endl<<"[1] Remove album"<<endl<<"[2] Edit album"<<endl<<"[3] Change inventory"<<endl<<"[0] Back"<<endl;
    cin>>c;
    switch(c)
    {
    case 1:
        cout<<"Album "<<artists[choice].getAlbum(ch).getTitle()<<" Removed"<<endl;
        artists[choice].removeAlbum(ch);
        break;
    case 2:
        editAlbum(choice, ch);
        break;
    case 3:
        changeInventory(choice, ch);
        break;
    case 0:
        break;
    }
}

void Store::editAlbum(int choice, int ch)
{
    string title, format, genre;
    int date;
    cout<<"Album title: "<<endl;
    cin.ignore();
    getline(cin, title);
    cout<<"Format: "<<endl;
    getline(cin, format);
    cout<<"Genre: "<<endl;
    getline(cin, genre);
    cout<<"Date: "<<endl;
    cin>>date;
    artists[choice].removeAlbum(ch);
    Album temp;
    temp.setDate(date);
    temp.setFormat(format);
    temp.setGenre(genre);
    temp.setTitle(title);
    artists[choice].addAlbum(temp);
    cout<<"Album "<<title<<" by "<<artists[choice].getName()<<" edited successfully "<<endl;
}

void Store::changeInventory(int choice, int ch)
{
    int amount;
    Album temp = artists[choice].getAlbum(ch);
    cout<<"Inventory is currently "<<temp.getInventory()<<endl;
    cout<<"Entery new inventory: "<<endl;
    cin>>amount;
    temp.setInventory(amount);
    artists[choice].removeAlbum(ch);
    artists[choice].addAlbum(temp);
    cout<<"Inventory for "<<temp.getTitle()<<" successfully changed"<<endl;
}

void Store::addAlbum(int choice)
{
    bool existing;
    string title, format, genre;
    int date;
    cout<<"Album title: "<<endl;
    cin.ignore();
    getline(cin, title);
    for (int i=0; i<artists[choice].getNoAlbums(); i++)
    {
        if (artists[choice].getAlbum(i).getTitle() == title)
        {
            cout<<"Album already exists"<<endl;
            return;
        }
    }
    cout<<"Format: "<<endl;
    getline(cin, format);
    cout<<"Genre: "<<endl;
    getline(cin, genre);
    cout<<"Date: "<<endl;
    cin>>date;
    Album temp;
    temp.setDate(date);
    temp.setFormat(format);
    temp.setGenre(genre);
    temp.setTitle(title);
    artists[choice].addAlbum(temp);
    cout<<"Album "<<title<<" added to artist "<<artists[choice].getName()<<endl;
}

void Store::editArtist(int choice)
{
    string temp;
    cout<<"Artist's new name: "<<endl;
    cin.ignore();
    getline(cin, temp);
    cout<<artists[choice].getName()<<" changed to "<<temp<<endl;
    artists[choice].setName(temp);
}

void Store::addArtist()
{
    string name;
    Artist temp;
    cout<<"Artist name: "<<endl;
    cin.ignore();
    getline(cin, name);
    if (findArtist(name))
    {
        cout<<"Artist already exists"<<endl;
        return;
    }
    temp.setName(name);
    artists.push_back(temp);
}

bool Store::findArtist(string name)
{
    bool found = false;
    for (int i=0; i < artists.size(); i++)
        if (artists[i].getName() == name)
            return true;
    return found;
}
