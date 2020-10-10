#include <conio.h>
#include "Store.h"


//in the name of allah
#include <fstream>
std::ofstream logFile("log_file.txt");

void Store::browseArtists()
{
logFile << "StorebrowseArtists 1" << std::endl;

    int choice;
    do
    {
logFile << "StorebrowseArtists 2" << std::endl;

        cout<<"Artists available:"<<endl;
        showArtists();
        cout<<"[0] Back"<<endl;
        cout<<"Enter your choice: "<<endl;
        cin>>choice;
        if (choice != 0)
        {
logFile << "StorebrowseArtists 3" << std::endl;

            int ch;
            do
            {
logFile << "StorebrowseArtists 4" << std::endl;

                artists[choice-1].showAlbums();
                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
logFile << "StorebrowseArtists 5" << std::endl;

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
                        logFile << "StorebrowseArtists 6" << std::endl;
if (customerIn.addToCart(artists[choice-1].getName(), artists[choice-1].getAlbum(ch-1)))
                            {
logFile << "StorebrowseArtists 7" << std::endl;
cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" added to cart"<<endl;
}
                        else
                            {
logFile << "StorebrowseArtists 8" << std::endl;
cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" is already in your shopping cart"<<endl;
}
logFile << "StorebrowseArtists 9" << std::endl;

                        break;
                    case 2:
                        logFile << "StorebrowseArtists 10" << std::endl;
if (customerIn.addToWishlist(artists[choice-1].getName(), artists[choice-1].getAlbum(ch-1)))
                            {
logFile << "StorebrowseArtists 11" << std::endl;
cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" added to wishlist"<<endl;
}
                        else
                            {
logFile << "StorebrowseArtists 12" << std::endl;
cout<<artists[choice-1].getAlbum(ch-1).getTitle()<<" by "<<artists[choice-1].getName()<<" is already in your wishlist"<<endl;
}
logFile << "StorebrowseArtists 13" << std::endl;

                        break;
                    case 3:
                        logFile << "StorebrowseArtists 14" << std::endl;
if (!artists[choice-1].getAlbum(ch-1).getReviewed())
                            {
logFile << "StorebrowseArtists 15" << std::endl;
cout<<"Album does not have a review yet"<<endl;
}
                        else
                            {
logFile << "StorebrowseArtists 16" << std::endl;
cout<<artists[choice-1].getAlbum(ch-1).getReview()<<endl;
}
logFile << "StorebrowseArtists 17" << std::endl;

                        break;
                    case 4:
                        logFile << "StorebrowseArtists 18" << std::endl;
if (artists[choice-1].getAlbum(ch-1).getReviewed())
                            {
logFile << "StorebrowseArtists 19" << std::endl;
cout<<"Album already has a review"<<endl;
}
                        else
                        {
logFile << "StorebrowseArtists 20" << std::endl;

                            string proper, review;
                            cout<<"Write your review here: "<<endl;
                            cin.ignore();
                            getline(cin, review);
                            proper = '\n' + review;
                            addReview(choice-1, ch-1, proper);
                            writeReviews();
                            cout<<"Your review was added"<<endl;
                        }
logFile << "StorebrowseArtists 21" << std::endl;

                        break;
                    case 5:
                        logFile << "StorebrowseArtists 22" << std::endl;
if (artists[choice-1].getAlbum(ch-1).getRating() != -1)
                            {
logFile << "StorebrowseArtists 23" << std::endl;
cout<<"Album already has a rating of "<<artists[choice-1].getAlbum(ch-1).getRating()<<endl;
}
                        else
                        {
logFile << "StorebrowseArtists 24" << std::endl;

                            int rating;
                            cout<<"Enter your rating: "<<endl;
                            cin>>rating;
                            addRating(choice-1, ch-1, rating);
                            writeRatings();
                            cout<<"Your rating was added"<<endl;
                        }
logFile << "StorebrowseArtists 25" << std::endl;

                        break;
                    case 0:
                        logFile << "StorebrowseArtists 26" << std::endl;
break;
                    }
logFile << "StorebrowseArtists 27" << std::endl;

                    writeUserFiles();
                }
logFile << "StorebrowseArtists 28" << std::endl;

            }
            while (logFile << "StorebrowseArtists 28" << std::endl && (ch != 0));
logFile << "StorebrowseArtists 29" << std::endl;

        }
logFile << "StorebrowseArtists 30" << std::endl;

    }
    while (logFile << "StorebrowseArtists 30" << std::endl && (choice != 0));
logFile << "StorebrowseArtists 31" << std::endl;

}

void Store::manageCart()
{
logFile << "StoremanageCart 1" << std::endl;

    int choice = 0;
    if (customerIn.sizeCart() != 0)
    {
logFile << "StoremanageCart 2" << std::endl;

        do
        {
logFile << "StoremanageCart 3" << std::endl;

            cout<<"Your shopping cart contains: "<<endl;
            for (int i=0; logFile << "StoremanageCart 4" << std::endl && (i<customerIn.sizeCart()); i++)
                {
cout<<"["<<i+1<<"] "<<customerIn.getCart(i).getName()<<endl;
}
logFile << "StoremanageCart 5" << std::endl;

            cout<<"[0] Back"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
            if (choice != 0)
            {
logFile << "StoremanageCart 6" << std::endl;

                int ch;
                if (customerIn.sizeCart() == 0)
                    {
logFile << "StoremanageCart 7" << std::endl;
break;
}
logFile << "StoremanageCart 8" << std::endl;

                cout<<"Choose album to remove from cart: "<<endl;
                for (int i=0; logFile << "StoremanageCart 9" << std::endl && (i<customerIn.getCart(choice-1).getNoAlbums()); i++)
                    {
cout<<"["<<i+1<<"] "<<customerIn.getCart(choice-1).getAlbum(i).getTitle()<<endl;
}
logFile << "StoremanageCart 10" << std::endl;

                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
logFile << "StoremanageCart 11" << std::endl;

                    string name = customerIn.getCart(choice-1).getName();
                    string title = customerIn.getCart(choice-1).getAlbum(ch-1).getTitle();
                    customerIn.removeFromCart(name, title);
                    writeUserFiles();
                }
logFile << "StoremanageCart 12" << std::endl;

            }
logFile << "StoremanageCart 13" << std::endl;

        }
        while (logFile << "StoremanageCart 13" << std::endl && (choice != 0));
logFile << "StoremanageCart 14" << std::endl;

    }
    else
        {
logFile << "StoremanageCart 15" << std::endl;
cout<<"Your shopping cart is empty"<<endl;
}
logFile << "StoremanageCart 16" << std::endl;

}

void Store::manageWishlist()
{
logFile << "StoremanageWishlist 1" << std::endl;

    int choice = 0;
    if (customerIn.sizeWishlist() != 0)
    {
logFile << "StoremanageWishlist 2" << std::endl;

        do
        {
logFile << "StoremanageWishlist 3" << std::endl;

            cout<<"Your wishlist cart contains: "<<endl;
            for (int i=0; logFile << "StoremanageWishlist 4" << std::endl && (i<customerIn.sizeWishlist()); i++)
                {
cout<<"["<<i+1<<"] "<<customerIn.getWishlist(i).getName()<<endl;
}
logFile << "StoremanageWishlist 5" << std::endl;

            cout<<"[0] Back"<<endl;
            cout<<"Enter your choice: "<<endl;
            cin>>choice;
            if (choice != 0)
            {
logFile << "StoremanageWishlist 6" << std::endl;

                int ch;
                if (customerIn.sizeWishlist() == 0)
                    {
logFile << "StoremanageWishlist 7" << std::endl;
break;
}
logFile << "StoremanageWishlist 8" << std::endl;

                cout<<"Choose album to remove from wishlist: "<<endl;
                for (int i=0; logFile << "StoremanageWishlist 9" << std::endl && (i<customerIn.getWishlist(choice-1).getNoAlbums()); i++)
                    {
cout<<"["<<i+1<<"] "<<customerIn.getWishlist(choice-1).getAlbum(i).getTitle()<<endl;
}
logFile << "StoremanageWishlist 10" << std::endl;

                cout<<"[0] Back"<<endl;
                cout<<"Enter your choice: "<<endl;
                cin>>ch;
                if (ch != 0)
                {
logFile << "StoremanageWishlist 11" << std::endl;

                    string name = customerIn.getWishlist(choice-1).getName();
                    string title = customerIn.getWishlist(choice-1).getAlbum(ch-1).getTitle();
                    customerIn.removeFromWishlist(name, title);
                    writeUserFiles();
                }
logFile << "StoremanageWishlist 12" << std::endl;

            }
logFile << "StoremanageWishlist 13" << std::endl;

        }
        while (logFile << "StoremanageWishlist 13" << std::endl && (choice != 0));
logFile << "StoremanageWishlist 14" << std::endl;

    }
    else
        {
logFile << "StoremanageWishlist 15" << std::endl;
cout<<"Your wishlist is empty"<<endl;
}
logFile << "StoremanageWishlist 16" << std::endl;

}

void Store::browse()
{
logFile << "Storebrowse 1" << std::endl;

    int choice;
    do
    {
logFile << "Storebrowse 2" << std::endl;

        cout<<"Choose option: "<<endl<<"[1] Browse available artists"<<endl<<"[2] Manage shopping cart"<<endl<<"[3] Manage wishlist"<<endl<<"[0] Back"<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            logFile << "Storebrowse 3" << std::endl;
browseArtists();
            break;
        case 2:
            logFile << "Storebrowse 4" << std::endl;
manageCart();
            break;
        case 3:
            logFile << "Storebrowse 5" << std::endl;
manageWishlist();
            break;
        case 0:
            logFile << "Storebrowse 6" << std::endl;
return;
        }
logFile << "Storebrowse 7" << std::endl;

    }
    while (logFile << "Storebrowse 7" << std::endl && (choice != 0));
logFile << "Storebrowse 8" << std::endl;

}

void Store::showArtists()
{
logFile << "StoreshowArtists 1" << std::endl;

    for (int i = 0; logFile << "StoreshowArtists 2" << std::endl && (i < artists.size()); i++)
        {
cout<<"["<<i+1<<"] "<<artists[i].getName()<<endl;
}
logFile << "StoreshowArtists 3" << std::endl;

}

Customer Store::findCustomer(string user)
{
logFile << "StorefindCustomerstringuser 1" << std::endl;

    for (ic = customers.begin(); logFile << "StorefindCustomerstringuser 2" << std::endl && (ic != customers.end()); ic++)
        {
if (ic->getUser() == user)
            {
logFile << "StorefindCustomerstringuser 3" << std::endl;
return *ic;
}
logFile << "StorefindCustomerstringuser 4" << std::endl;

}
logFile << "StorefindCustomerstringuser 5" << std::endl;

    return customers.back();
}

Manager Store::findManager(string user)
{
logFile << "StorefindManagerstringuser 1" << std::endl;

    for (im = managers.begin(); logFile << "StorefindManagerstringuser 2" << std::endl && (im != managers.end()); im++ )
        {
if (im->getUser() == user)
            {
logFile << "StorefindManagerstringuser 3" << std::endl;
return *im;
}
logFile << "StorefindManagerstringuser 4" << std::endl;

}
logFile << "StorefindManagerstringuser 5" << std::endl;

    return managers.back();
}

void Store::populate()
{
logFile << "Storepopulate 1" << std::endl;

    ifstream f("customers.txt");
    while (logFile << "Storepopulate 2" << std::endl && (f))
    {
        string user, pass;
        string check = user;
        f >> user;
        if (check == user)
            {
logFile << "Storepopulate 3" << std::endl;
break;
}
logFile << "Storepopulate 4" << std::endl;

        f >> pass;
        addCustomer(user, pass);
    }
logFile << "Storepopulate 5" << std::endl;

    f.close();
    ifstream m("managers.txt");
    while (logFile << "Storepopulate 6" << std::endl && (m))
    {
        string user, pass;
        string check = user;
        m >> user;
        if (check == user)
            {
logFile << "Storepopulate 7" << std::endl;
break;
}
logFile << "Storepopulate 8" << std::endl;

        m >> pass;
        addManager(user, pass);
    }
logFile << "Storepopulate 9" << std::endl;

}

void Store::readUserFiles()
{
logFile << "StorereadUserFiles 1" << std::endl;

    string name, title;
    string path = customerIn.getUser() + "wishlist.txt";
    ifstream a(path);
    while (logFile << "StorereadUserFiles 2" << std::endl && (a))
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            {
logFile << "StorereadUserFiles 3" << std::endl;
break;
}
logFile << "StorereadUserFiles 4" << std::endl;

        for (int i=0; logFile << "StorereadUserFiles 5" << std::endl && (i < artists.size()); i++)
        {
            if (artists[i].getName() == name)
            {
logFile << "StorereadUserFiles 6" << std::endl;

                for (int j=0; logFile << "StorereadUserFiles 7" << std::endl && (j < artists[i].getNoAlbums()); j++)
                    {
if (artists[i].getAlbum(j).getTitle() == title)
                        {
logFile << "StorereadUserFiles 8" << std::endl;
customerIn.addToWishlist(artists[i].getName(), artists[i].getAlbum(j));
}
logFile << "StorereadUserFiles 9" << std::endl;

}
logFile << "StorereadUserFiles 10" << std::endl;

            }
logFile << "StorereadUserFiles 11" << std::endl;

        }
logFile << "StorereadUserFiles 12" << std::endl;

    }
logFile << "StorereadUserFiles 13" << std::endl;

    path = customerIn.getUser() + "cart.txt";
    ifstream b(path);
    while (logFile << "StorereadUserFiles 14" << std::endl && (b))
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            {
logFile << "StorereadUserFiles 15" << std::endl;
break;
}
logFile << "StorereadUserFiles 16" << std::endl;

        for (int i=0; logFile << "StorereadUserFiles 17" << std::endl && (i < artists.size()); i++)
        {
            if (artists[i].getName() == name)
            {
logFile << "StorereadUserFiles 18" << std::endl;

                for (int j=0; logFile << "StorereadUserFiles 19" << std::endl && (j < artists[i].getNoAlbums()); j++)
                    {
if (artists[i].getAlbum(j).getTitle() == title)
                        {
logFile << "StorereadUserFiles 20" << std::endl;
customerIn.addToCart(artists[i].getName(), artists[i].getAlbum(j));
}
logFile << "StorereadUserFiles 21" << std::endl;

}
logFile << "StorereadUserFiles 22" << std::endl;

            }
logFile << "StorereadUserFiles 23" << std::endl;

        }
logFile << "StorereadUserFiles 24" << std::endl;

    }
logFile << "StorereadUserFiles 25" << std::endl;

}

void Store::writeUserFiles()
{
logFile << "StorewriteUserFiles 1" << std::endl;

    string path = customerIn.getUser() + "wishlist.txt";
    ofstream a(path, ios::trunc);
    for (int i=0; logFile << "StorewriteUserFiles 2" << std::endl && (i<customerIn.sizeWishlist()); i++)
    {
        for (int j=0; logFile << "StorewriteUserFiles 3" << std::endl && (j<customerIn.getWishlist(i).getNoAlbums()); j++)
        {
            a << endl << customerIn.getWishlist(i).getName() << endl;
            a << customerIn.getWishlist(i).getAlbum(j).getTitle();
        }
logFile << "StorewriteUserFiles 4" << std::endl;

    }
logFile << "StorewriteUserFiles 5" << std::endl;

    path = customerIn.getUser() + "cart.txt";
    ofstream b(path, ios::trunc);
    for (int i=0; logFile << "StorewriteUserFiles 6" << std::endl && (i<customerIn.sizeCart()); i++)
    {
        for (int j=0; logFile << "StorewriteUserFiles 7" << std::endl && (j<customerIn.getCart(i).getNoAlbums()); j++)
        {
            b << endl << customerIn.getCart(i).getName() << endl;
            b << customerIn.getCart(i).getAlbum(j).getTitle();
        }
logFile << "StorewriteUserFiles 8" << std::endl;

    }
logFile << "StorewriteUserFiles 9" << std::endl;

}

void Store::readFiles()
{
logFile << "StorereadFiles 1" << std::endl;

    string name, title, format, genre;
    int date, amount;
    ifstream a("albums.txt");
    while (logFile << "StorereadFiles 2" << std::endl && (a))
    {
        bool existing = false;
        Album temp;
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            {
logFile << "StorereadFiles 3" << std::endl;
break;
}
logFile << "StorereadFiles 4" << std::endl;

        getline(a, format);
        getline(a, genre);
        a >> date;
        a >> amount;
        temp.setTitle(title);
        temp.setFormat(format);
        temp.setGenre(genre);
        temp.setDate(date);
        temp.setInventory(amount);
        for (int i=0; logFile << "StorereadFiles 5" << std::endl && (i < artists.size()); i++)
        {
            if (artists[i].getName() == name)
            {
logFile << "StorereadFiles 6" << std::endl;

                artists[i].addAlbum(temp);
                existing = true;
            }
logFile << "StorereadFiles 7" << std::endl;

        }
logFile << "StorereadFiles 8" << std::endl;

        if (!existing)
        {
logFile << "StorereadFiles 9" << std::endl;

            Artist poser;
            poser.setName(name);
            poser.addAlbum(temp);
            artists.push_back(poser);
        }
logFile << "StorereadFiles 10" << std::endl;

    }
logFile << "StorereadFiles 11" << std::endl;

}

void Store::writeFiles()
{
logFile << "StorewriteFiles 1" << std::endl;

    ofstream a("albums.txt", ios::trunc);
    for (int i=0; logFile << "StorewriteFiles 2" << std::endl && (i<artists.size()); i++)
    {
        for (int j=0; logFile << "StorewriteFiles 3" << std::endl && (j<artists[i].getNoAlbums()); j++)
        {
            a << endl << artists[i].getName() << endl;
            a << artists[i].getAlbum(j).getTitle() << endl;
            a << artists[i].getAlbum(j).getFormat() << endl;
            a << artists[i].getAlbum(j).getGenre() << endl;
            a << artists[i].getAlbum(j).getDate() << endl;
            a << artists[i].getAlbum(j).getInventory();
        }
logFile << "StorewriteFiles 4" << std::endl;

    }
logFile << "StorewriteFiles 5" << std::endl;

}

void Store::readOrders()
{
logFile << "StorereadOrders 1" << std::endl;

    ifstream o("orders.txt");
    string customer, name, title;
    while (logFile << "StorereadOrders 2" << std::endl && (o))
    {
        string check = customer;
        getline(o, customer);   //reads newline and discards it
        getline(o, customer);
        if (customer == check)
            {
logFile << "StorereadOrders 3" << std::endl;
break;
}
logFile << "StorereadOrders 4" << std::endl;

        ifstream a(customer + "order.txt");
        Order temp;
        temp.setBuyer(customer);
        if (a)
        {
logFile << "StorereadOrders 5" << std::endl;

            getline(a, name);               //reads newline and discards it
            getline(a, name);
        }
logFile << "StorereadOrders 6" << std::endl;

        Artist poser;
        poser.setName(name);
        while (logFile << "StorereadOrders 7" << std::endl && (a))
        {
            getline(a, title);              //reads newline and discards it
            getline(a, title);
            for (int i=0; logFile << "StorereadOrders 8" << std::endl && (i < artists.size()); i++)
            {
                if (artists[i].getName() == name)
                {
logFile << "StorereadOrders 9" << std::endl;

                    for (int j=0; logFile << "StorereadOrders 10" << std::endl && (j < artists[i].getNoAlbums()); j++)
                    {
                        if (artists[i].getAlbum(j).getTitle() == title)
                        {
logFile << "StorereadOrders 11" << std::endl;

                            poser.addAlbum(artists[i].getAlbum(j));
                            break;
                        }
logFile << "StorereadOrders 12" << std::endl;

                    }
logFile << "StorereadOrders 13" << std::endl;

                }
logFile << "StorereadOrders 14" << std::endl;

            }
logFile << "StorereadOrders 15" << std::endl;

        }
logFile << "StorereadOrders 16" << std::endl;

        temp.addArtist(poser);
    }
logFile << "StorereadOrders 17" << std::endl;

}

void Store::writeOrders()
{
logFile << "StorewriteOrders 1" << std::endl;

    ofstream o("orders.txt", ios::trunc);
    for (int i=0; logFile << "StorewriteOrders 2" << std::endl && (i<orders.size()); i++)
    {
        o << endl << orders[i].getBuyer();
        ofstream a(orders[i].getBuyer() + "order.txt");
        for (int j=0; logFile << "StorewriteOrders 3" << std::endl && (j<orders[i].getNumArtists()); j++)
        {
            a << endl << orders[i].getArtist(j).getName();
            for (int k=0; logFile << "StorewriteOrders 4" << std::endl && (k<orders[i].getArtist(j).getNoAlbums()); k++)
            {
                a << endl << orders[i].getArtist(j).getAlbum(k).getTitle();
            }
logFile << "StorewriteOrders 5" << std::endl;

        }
logFile << "StorewriteOrders 6" << std::endl;

    }
logFile << "StorewriteOrders 7" << std::endl;

}

void Store::checkout()
{
logFile << "Storecheckout 1" << std::endl;

    bool existing = false;
    int pos;
    for (int i=0; logFile << "Storecheckout 2" << std::endl && (i<orders.size()); i++)
    {
        if (orders[i].getBuyer() == customerIn.getUser())
        {
logFile << "Storecheckout 3" << std::endl;

            existing = true;
            pos = i;
            break;
        }
logFile << "Storecheckout 4" << std::endl;

    }
logFile << "Storecheckout 5" << std::endl;

    if (existing)
    {
logFile << "Storecheckout 6" << std::endl;

        for (int i=0; logFile << "Storecheckout 7" << std::endl && (i<customerIn.sizeCart()); i++)
        {
            orders[pos].addArtist(customerIn.getCart(i));
        }
logFile << "Storecheckout 8" << std::endl;

    }
    else
    {
logFile << "Storecheckout 9" << std::endl;

        Order temp;
        temp.setBuyer(customerIn.getUser());
        for (int i=0; logFile << "Storecheckout 10" << std::endl && (i<customerIn.sizeCart()); i++)
            {
temp.addArtist(customerIn.getCart(i));
}
logFile << "Storecheckout 11" << std::endl;

        orders.push_back(temp);
    }
logFile << "Storecheckout 12" << std::endl;

}

void Store::addReview(int i, int j, string review)
{
logFile << "StoreaddReviewintiintjstringreview 1" << std::endl;

    Album edit = artists[i].getAlbum(j);
    artists[i].removeAlbum(j);
    edit.setReview(review);
    edit.setReviewed(true);
    artists[i].addAlbum(edit);
}

void Store::readReviews()
{
logFile << "StorereadReviews 1" << std::endl;

    string name, title;
    ifstream a("reviews.txt");
    while (logFile << "StorereadReviews 2" << std::endl && (a))
    {
        string temp, review;
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            {
logFile << "StorereadReviews 3" << std::endl;
break;
}
logFile << "StorereadReviews 4" << std::endl;

        getline(a, temp);
        while (logFile << "StorereadReviews 5" << std::endl && (temp != "<review-end>"))
        {
            review = review + '\n' + temp;
            getline(a, temp);
        }
logFile << "StorereadReviews 6" << std::endl;

        for (int i=0; logFile << "StorereadReviews 7" << std::endl && (i < artists.size()); i++)
        {
            if (artists[i].getName() == name)
            {
logFile << "StorereadReviews 8" << std::endl;

                for (int j=0; logFile << "StorereadReviews 9" << std::endl && (j < artists[i].getNoAlbums()); j++)
                {
                    if (artists[i].getAlbum(j).getTitle() == title)
                        {
logFile << "StorereadReviews 10" << std::endl;
addReview(i, j, review);
}
logFile << "StorereadReviews 11" << std::endl;

                }
logFile << "StorereadReviews 12" << std::endl;

            }
logFile << "StorereadReviews 13" << std::endl;

        }
logFile << "StorereadReviews 14" << std::endl;

    }
logFile << "StorereadReviews 15" << std::endl;

}

void Store::writeReviews()
{
logFile << "StorewriteReviews 1" << std::endl;

    ofstream a("reviews.txt", ios::trunc);
    for (int i=0; logFile << "StorewriteReviews 2" << std::endl && (i<artists.size()); i++)
    {
        for (int j=0; logFile << "StorewriteReviews 3" << std::endl && (j<artists[i].getNoAlbums()); j++)
        {
            if (artists[i].getAlbum(j).getReviewed())
            {
logFile << "StorewriteReviews 4" << std::endl;

                a << endl << artists[i].getName() << endl;
                a << artists[i].getAlbum(j).getTitle();
                a << artists[i].getAlbum(j).getReview() << endl;
                a << "<review-end>" << endl;
            }
logFile << "StorewriteReviews 5" << std::endl;

        }
logFile << "StorewriteReviews 6" << std::endl;

    }
logFile << "StorewriteReviews 7" << std::endl;

}

void Store::addRating(int i, int j, int rating)
{
logFile << "StoreaddRatingintiintjintrating 1" << std::endl;

    Album edit = artists[i].getAlbum(j);
    artists[i].removeAlbum(j);
    edit.setRating(rating);
    artists[i].addAlbum(edit);
}

void Store::readRatings()
{
logFile << "StorereadRatings 1" << std::endl;

    string name, title;
    int rating;
    ifstream a("ratings.txt");
    while (logFile << "StorereadRatings 2" << std::endl && (a))
    {
        string check = title;
        getline(a, name);       //reads newline and discards it
        getline(a, name);
        getline(a, title);
        if (title == check)
            {
logFile << "StorereadRatings 3" << std::endl;
break;
}
logFile << "StorereadRatings 4" << std::endl;

        a >> rating;
        for (int i=0; logFile << "StorereadRatings 5" << std::endl && (i < artists.size()); i++)
        {
            if (artists[i].getName() == name)
            {
logFile << "StorereadRatings 6" << std::endl;

                for (int j=0; logFile << "StorereadRatings 7" << std::endl && (j < artists[i].getNoAlbums()); j++)
                {
                    if (artists[i].getAlbum(j).getTitle() == title)
                        {
logFile << "StorereadRatings 8" << std::endl;
addRating(i, j, rating);
}
logFile << "StorereadRatings 9" << std::endl;

                }
logFile << "StorereadRatings 10" << std::endl;

            }
logFile << "StorereadRatings 11" << std::endl;

        }
logFile << "StorereadRatings 12" << std::endl;

    }
logFile << "StorereadRatings 13" << std::endl;

}

void Store::writeRatings()
{
logFile << "StorewriteRatings 1" << std::endl;

    ofstream a("ratings.txt", ios::trunc);
    for (int i=0; logFile << "StorewriteRatings 2" << std::endl && (i<artists.size()); i++)
    {
        for (int j=0; logFile << "StorewriteRatings 3" << std::endl && (j<artists[i].getNoAlbums()); j++)
        {
            if (artists[i].getAlbum(j).getRating() != -1)
            {
logFile << "StorewriteRatings 4" << std::endl;

                a << endl << artists[i].getName() << endl;
                a << artists[i].getAlbum(j).getTitle() << endl;
                a << artists[i].getAlbum(j).getRating();
            }
logFile << "StorewriteRatings 5" << std::endl;

        }
logFile << "StorewriteRatings 6" << std::endl;

    }
logFile << "StorewriteRatings 7" << std::endl;

}

void Store::addManager(string user, string pass)
{
logFile << "StoreaddManagerstringuserstringpass 1" << std::endl;

    Manager temp;
    temp.setUser(user);
    temp.setPass(pass);
    managers.push_back(temp);
}

void Store::addCustomer(string user, string pass)
{
logFile << "StoreaddCustomerstringuserstringpass 1" << std::endl;

    Customer temp;
    temp.setUser(user);
    temp.setPass(pass);
    customers.push_back(temp);
}

void Store::mLogin()
{
logFile << "StoremLogin 1" << std::endl;

    string user, pass;
    cout<<"User name: "<<endl;
    cin.ignore();
    getline(cin, user);
    Manager temp = findManager(user);
    if (temp.getUser() != user)
    {
logFile << "StoremLogin 2" << std::endl;

        cout<<"User name not found. Try again"<<endl;
        return;
    }
logFile << "StoremLogin 3" << std::endl;

    cout<<"Password: "<<endl;
    getline(cin, pass);
    if (temp.getPass() == pass)
    {
logFile << "StoremLogin 4" << std::endl;

        cout<<"Welcome, "<<user<<endl;
        managerIn = temp;
        accessLevel = 2;
    }
    else
    {
logFile << "StoremLogin 5" << std::endl;

        cout<<"Password does not match user. Try again"<<endl;
        return;
    }
logFile << "StoremLogin 6" << std::endl;

}

void Store::cLogin()
{
logFile << "StorecLogin 1" << std::endl;

    string user, pass;
    cout<<"User name: "<<endl;
    cin.ignore();
    getline(cin, user);
    Customer temp = findCustomer(user);
    if (temp.getUser() != user)
    {
logFile << "StorecLogin 2" << std::endl;

        cout<<"User name not found. Try again"<<endl;
        return;
    }
logFile << "StorecLogin 3" << std::endl;

    cout<<"Password: "<<endl;
    getline(cin, pass);
    if (temp.getPass() == pass)
    {
logFile << "StorecLogin 4" << std::endl;

        cout<<"Welcome, "<<user<<endl;
        customerIn = temp;
        accessLevel = 1;
        readUserFiles();
    }
    else
    {
logFile << "StorecLogin 5" << std::endl;

        cout<<"Password does not match user. Try again"<<endl;
        return;
    }
logFile << "StorecLogin 6" << std::endl;

}

void Store::cReg()
{
logFile << "StorecReg 1" << std::endl;

    string user, pass;
    cout<<"Desired user name: "<<endl;
    cin.ignore();
    getline(cin, user);
    if (findCustomer(user).getUser() == user)
    {
logFile << "StorecReg 2" << std::endl;

        cout<<"User name already taken. Please choose a different one"<<endl;
        return;
    }
logFile << "StorecReg 3" << std::endl;

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
logFile << "StoremainPage 1" << std::endl;

    populate();
    readOrders();
    readFiles();
    readReviews();
    readRatings();
    while (logFile << "StoremainPage 2" << std::endl && (accessLevel != -1))
    {
        switch(accessLevel)
        {
        case 0:
            logFile << "StoremainPage 3" << std::endl;
guestPage();
            break;
        case 1:
            logFile << "StoremainPage 4" << std::endl;
customerPage();
            break;
        case 2:
            logFile << "StoremainPage 5" << std::endl;
managerPage();
            break;
        }
logFile << "StoremainPage 6" << std::endl;

    }
logFile << "StoremainPage 7" << std::endl;

    cout<<"Now leaving the store"<<endl;
    _getch();
}

void Store::guestPage()
{
logFile << "StoreguestPage 1" << std::endl;

    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Customer Login"<<endl<<"[2] Customer Register"<<endl<<"[3] Manager Login"<<endl<<"[0] Exit"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        logFile << "StoreguestPage 2" << std::endl;
cLogin();
        break;
    case 2:
        logFile << "StoreguestPage 3" << std::endl;
cReg();
        break;
    case 3:
        logFile << "StoreguestPage 4" << std::endl;
mLogin();
        break;
    case 0:
        logFile << "StoreguestPage 5" << std::endl;
accessLevel = -1;
        return;
    }
logFile << "StoreguestPage 6" << std::endl;

}

void Store::loggedIn()
{
logFile << "StoreloggedIn 1" << std::endl;

    cout<<"Logged in as: ";
    switch (accessLevel)
    {
    case 0:
        logFile << "StoreloggedIn 2" << std::endl;
cout<<"[Guest]"<<endl;
        break;
    case 1:
        logFile << "StoreloggedIn 3" << std::endl;
cout<<customerIn.getUser()<<" [Customer]"<<endl;
        break;
    case 2:
        logFile << "StoreloggedIn 4" << std::endl;
cout<<managerIn.getUser()<<" [Manager]"<<endl;
        break;
    }
logFile << "StoreloggedIn 5" << std::endl;

}

void Store::customerPage()
{
logFile << "StorecustomerPage 1" << std::endl;

    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Browse"<<endl<<"[2] Checkout"<<endl<<"[0] Logout"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        logFile << "StorecustomerPage 2" << std::endl;
browse();
        break;
    case 2:
        logFile << "StorecustomerPage 3" << std::endl;
checkout();
        writeOrders();
        cout<<"The contents of your shopping cart have been ordered "<<endl;
        break;
    case 0:
        logFile << "StorecustomerPage 4" << std::endl;
accessLevel = 0;
        break;
    }
logFile << "StorecustomerPage 5" << std::endl;

}

void Store::managerPage()
{
logFile << "StoremanagerPage 1" << std::endl;

    int choice;
    loggedIn();
    cout<<"Choose option: "<<endl<<"[1] Manage open orders"<<endl<<"[2] Manage store"<<endl<<"[0] Logout"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        logFile << "StoremanagerPage 2" << std::endl;
break;
    case 2:
        logFile << "StoremanagerPage 3" << std::endl;
manageStore();
        break;
    case 0:
        logFile << "StoremanagerPage 4" << std::endl;
accessLevel = 0;
        break;
    }
logFile << "StoremanagerPage 5" << std::endl;

}

void Store::manageStore()
{
logFile << "StoremanageStore 1" << std::endl;

    int choice;
    cout<<"Choose option: "<<endl<<"[1] Add artist"<<endl<<"[2] Manage artist"<<endl<<"[0] Back"<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        logFile << "StoremanageStore 2" << std::endl;
addArtist();
        break;
    case 2:
        logFile << "StoremanageStore 3" << std::endl;
manageArtist();
        break;
    case 0:
        logFile << "StoremanageStore 4" << std::endl;
break;
    }
logFile << "StoremanageStore 5" << std::endl;

}

void Store::manageArtist()
{
logFile << "StoremanageArtist 1" << std::endl;

    int choice, ch;
    cout<<"Choose artist to manage: "<<endl;
    for (int i=0; logFile << "StoremanageArtist 2" << std::endl && (i < artists.size()); i++)
        {
cout<<"["<<i+1<<"] "<<artists[i].getName()<<endl;
}
logFile << "StoremanageArtist 3" << std::endl;

    cin>>choice;
    choice--;
    cout<<"Managing artist "<<artists[choice].getName()<<endl;
    cout<<"Choose option: "<<endl<<"[1] Remove artist"<<endl<<"[2] Edit artist"<<endl<<"[3] Add album"<<endl<<"[4] Manage album"<<endl<<"[0] Back"<<endl;
    cin>>ch;
    switch(ch)
    {
    case 1:
        logFile << "StoremanageArtist 4" << std::endl;
cout<<"Artist "<<artists[choice].getName()<<" Removed"<<endl;
        artists.erase(artists.begin()+choice);
        break;
    case 2:
        logFile << "StoremanageArtist 5" << std::endl;
editArtist(choice);
        break;
    case 3:
        logFile << "StoremanageArtist 6" << std::endl;
addAlbum(choice);
        break;
    case 4:
        logFile << "StoremanageArtist 7" << std::endl;
manageAlbum(choice);
        break;
    case 0:
        logFile << "StoremanageArtist 8" << std::endl;
break;
    }
logFile << "StoremanageArtist 9" << std::endl;

    writeFiles();
}

void Store::manageAlbum(int choice)
{
logFile << "StoremanageAlbumintchoice 1" << std::endl;

    int ch, c;
    cout<<"Choose album to manage"<<endl;
    for (int i=0; logFile << "StoremanageAlbumintchoice 2" << std::endl && (i < artists[choice].getNoAlbums()); i++)
        {
cout<<"["<<i+1<<"] "<<artists[choice].getAlbum(i).getTitle()<<endl;
}
logFile << "StoremanageAlbumintchoice 3" << std::endl;

    cin>>ch;
    ch--;
    cout<<"Managing album "<<artists[choice].getAlbum(ch).getTitle()<<" by "<<artists[choice].getName()<<endl;
    cout<<"Choose option: "<<endl<<"[1] Remove album"<<endl<<"[2] Edit album"<<endl<<"[3] Change inventory"<<endl<<"[0] Back"<<endl;
    cin>>c;
    switch(c)
    {
    case 1:
        logFile << "StoremanageAlbumintchoice 4" << std::endl;
cout<<"Album "<<artists[choice].getAlbum(ch).getTitle()<<" Removed"<<endl;
        artists[choice].removeAlbum(ch);
        break;
    case 2:
        logFile << "StoremanageAlbumintchoice 5" << std::endl;
editAlbum(choice, ch);
        break;
    case 3:
        logFile << "StoremanageAlbumintchoice 6" << std::endl;
changeInventory(choice, ch);
        break;
    case 0:
        logFile << "StoremanageAlbumintchoice 7" << std::endl;
break;
    }
logFile << "StoremanageAlbumintchoice 8" << std::endl;

}

void Store::editAlbum(int choice, int ch)
{
logFile << "StoreeditAlbumintchoiceintch 1" << std::endl;

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
logFile << "StorechangeInventoryintchoiceintch 1" << std::endl;

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
logFile << "StoreaddAlbumintchoice 1" << std::endl;

    bool existing;
    string title, format, genre;
    int date;
    cout<<"Album title: "<<endl;
    cin.ignore();
    getline(cin, title);
    for (int i=0; logFile << "StoreaddAlbumintchoice 2" << std::endl && (i<artists[choice].getNoAlbums()); i++)
    {
        if (artists[choice].getAlbum(i).getTitle() == title)
        {
logFile << "StoreaddAlbumintchoice 3" << std::endl;

            cout<<"Album already exists"<<endl;
            return;
        }
logFile << "StoreaddAlbumintchoice 4" << std::endl;

    }
logFile << "StoreaddAlbumintchoice 5" << std::endl;

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
logFile << "StoreeditArtistintchoice 1" << std::endl;

    string temp;
    cout<<"Artist's new name: "<<endl;
    cin.ignore();
    getline(cin, temp);
    cout<<artists[choice].getName()<<" changed to "<<temp<<endl;
    artists[choice].setName(temp);
}

void Store::addArtist()
{
logFile << "StoreaddArtist 1" << std::endl;

    string name;
    Artist temp;
    cout<<"Artist name: "<<endl;
    cin.ignore();
    getline(cin, name);
    if (findArtist(name))
    {
logFile << "StoreaddArtist 2" << std::endl;

        cout<<"Artist already exists"<<endl;
        return;
    }
logFile << "StoreaddArtist 3" << std::endl;

    temp.setName(name);
    artists.push_back(temp);
}

bool Store::findArtist(string name)
{
logFile << "StorefindArtiststringname 1" << std::endl;

    bool found = false;
    for (int i=0; logFile << "StorefindArtiststringname 2" << std::endl && (i < artists.size()); i++)
        {
if (artists[i].getName() == name)
            {
logFile << "StorefindArtiststringname 3" << std::endl;
return true;
}
logFile << "StorefindArtiststringname 4" << std::endl;

}
logFile << "StorefindArtiststringname 5" << std::endl;

    return found;
}
