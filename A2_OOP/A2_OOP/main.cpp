#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Base class
//2. Implement the I / O system to parse the input file.Create a class for user input processing.
class Product {
protected:
    std::string name;
    double price;
    int quantity;

public:
    Product(std::string n, double p, int q) : name(n), price(p), quantity(q) {}

    virtual void displayProduct() {
        std::cout << "Name: " << name << ", Price: " << price << ", Quantity: " << quantity << std::endl;
    }

    // Getters
    std::string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    // Setters
    void setName(std::string n) { name = n; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }

};

// Derived class -----Electronics
class Electronics : public Product {
    std::string brand;
    std::string model;

public:
    Electronics(std::string n, double p, int q, std::string b, std::string m)
        : Product(n, p, q), brand(b), model(m) {}

    void displayProduct() override {
        Product::displayProduct();
        std::cout << "Brand: " << brand << ", Model: " << model << std::endl;
    }

};

// Derived class------Books
class Books : public Product {
    std::string author;
    std::string genre;
    std::string ISBN;

public:
    Books(std::string n, double p, int q, std::string a, std::string g, std::string isbn)
        : Product(n, p, q), author(a), genre(g), ISBN(isbn) {}

    void displayProduct() override {
        Product::displayProduct();
        std::cout << "Author: " << author << ", Genre: " << genre << ", ISBN: " << ISBN << std::endl;
    }

};

class Clothing : public Product {
    std::string size;
    std::string color;
    std::string material;

public:
    Clothing(std::string n, double p, int q, std::string s, std::string c, std::string m)
        : Product(n, p, q), size(s), color(c), material(m) {}

    void displayProduct() override {
        Product::displayProduct();
        std::cout << "Size: " << size << ", Color: " << color << ", Material: " << material << std::endl;
    }
    // Add more specific methods
};


class Order {
    int orderID;
    std::string customerName; // Customer detail
    std::vector<Product*> products; // List of products in the order
    double totalCost;
    std::string orderStatus;

public:
    Order(int id, std::string customer) : orderID(id), customerName(customer), totalCost(0.0), orderStatus("Pending") {}
    //3. Implement logic to store products.

    // Add a product to the order
    void addProduct(Product* product) {
        products.push_back(product);
        totalCost += product->getPrice(); // Assuming the price is for a single unit of product
    }

    // Calculate the total cost of the order
    void calculateTotalCost() {
        totalCost = 0.0;
        for (auto& product : products) {
            totalCost += product->getPrice() * product->getQuantity();
        }
    }

    // Getters and Setters
    int getOrderID() const { return orderID; }
    std::string getCustomerName() const { return customerName; }
    double getTotalCost() const { return totalCost; }
    std::string getOrderStatus() const { return orderStatus; }

    void setOrderStatus(const std::string& status) { orderStatus = status; }

    // Display order details
    void displayOrder() {
        std::cout << "Order ID: " << orderID << "\nCustomer: " << customerName << "\nTotal Cost: $" << totalCost << "\nStatus: " << orderStatus << std::endl;
        std::cout << "Products in Order:" << std::endl;
        for (auto& product : products) {
            product->displayProduct();
        }
    }

};


class ProductCatalog {
    std::vector<Product*> productList;

public:
    //4. Implement logic to buy products.
    // Add a product to the catalog
    void addProduct(Product* product) {
        productList.push_back(product);
    }

    // Display all products in the catalog
    void displayProducts() {
        for (auto& product : productList) {
            product->displayProduct();
        }
    }

    // Remove a product from the catalog
    void removeProduct(int productIndex) {
        if (productIndex >= 0 && productIndex < productList.size()) {
            productList.erase(productList.begin() + productIndex);
        }
        else {
            std::cout << "Invalid product index." << std::endl;
        }
    }

    // Find a product by name
    Product* findProductByName(const std::string& name) {
        for (auto& product : productList) {
            if (product->getName() == name) {
                return product;
            }
        }
        return nullptr;
    }

    // Update a product's details
    void updateProduct(int productIndex, std::string newName, double newPrice, int newQuantity) {
        if (productIndex >= 0 && productIndex < productList.size()) {
            productList[productIndex]->setName(newName);
            productList[productIndex]->setPrice(newPrice);
            productList[productIndex]->setQuantity(newQuantity);
        }
        else {
            std::cout << "Invalid product index." << std::endl;
        }
    }


};


//5. Test the solution, develop your own input data files.
void parseConfigFile(const std::string& filename, ProductCatalog& catalog) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string type, name, temp;
        double price;
        int quantity;
        std::getline(ss, type, ','); 

        if (type == "Electronics") {
            std::string brand, model, power;
            std::getline(ss, name, ',');
            ss >> price >> quantity;
            std::getline(ss, temp, ','); 
            std::getline(ss, brand, ',');
            std::getline(ss, model, ',');
            std::getline(ss, power, ',');
            Electronics* product = new Electronics(name, price, quantity, brand, model);
            catalog.addProduct(product);
        }
        else if (type == "Books") {
            std::string author, genre, isbn;
            std::getline(ss, name, ',');
            ss >> price >> quantity;
            std::getline(ss, temp, ','); 
            std::getline(ss, author, ',');
            std::getline(ss, genre, ',');
            std::getline(ss, isbn, ',');
            Books* product = new Books(name, price, quantity, author, genre, isbn);
            catalog.addProduct(product);
        }
        else if (type == "Clothing") {
            std::string size, color, material;
            std::getline(ss, name, ',');
            ss >> price >> quantity;
            std::getline(ss, temp, ',');
            std::getline(ss, size, ',');
            std::getline(ss, color, ',');
            std::getline(ss, material, ',');
            Clothing* product = new Clothing(name, price, quantity, size, color, material);
            catalog.addProduct(product);
        }
    }
}

int main() {
    ProductCatalog catalog;

    std::string configFilePath = "c.txt";

    // Parsw the configuration file to add products to the catalog
    parseConfigFile(configFilePath, catalog);

    std::cout << "All products in the catalog:" << std::endl;
    catalog.displayProducts();

  
    Order order(5, "V");
    Product* product = catalog.findProductByName("Smartphone"); 
    if (product) {
        order.addProduct(product);
    }

    std::cout << "\nOrder details:" << std::endl;
    order.displayOrder();

    return 0;
}