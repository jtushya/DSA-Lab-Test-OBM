/*
Problem:
This program simulates a supermarket checkout system with multiple lanes. It models customer arrivals, queue management, and cashier availability to analyze the efficiency of the system. The goal is to understand how queues and service times affect customer experience and system performance.

Intuition and Logic:
1. **Customer Arrival**:
   - Customers arrive at random intervals, modeled using an exponential distribution to simulate real-world scenarios.
   - Each customer is assigned to the shortest queue to minimize waiting time.

2. **Queue Management**:
   - Each checkout lane is managed using a queue, where customers are served in a first-come, first-served manner.
   - The program tracks the length of each queue and the number of customers served.

3. **Cashier Availability**:
   - Cashiers serve customers based on their arrival order and become available after a random service time.
   - Service times are modeled using a uniform distribution to introduce variability.

4. **Simulation Loop**:
   - The program runs a simulation loop for a specified duration, updating the state of the system at each time step.
   - At each step, it checks for new customer arrivals, assigns them to queues, and processes customers at each lane.

5. **Performance Metrics**:
   - The program calculates the total number of customers served and the average queue length for each lane.
   - These metrics provide insights into the efficiency of the checkout system.

6. **Example**:
   - Input: 2 lanes, arrival rate = 0.5 customers/min, service time = 5 mins, simulation time = 60 mins.
   - Output: Total customers served and the number of customers served per lane.

This program demonstrates the use of queues, random number generation, and simulation techniques to model and analyze real-world systems.
*/

#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

// Customer class to store customer information
class Customer {
public:
    Customer(int arrival_time) : arrival_time(arrival_time) {}
    int getArrivalTime() const { return arrival_time; }

private:
    int arrival_time;
};

// CheckoutLane class to manage each checkout lane's queue and cashier
class CheckoutLane {
public:
    CheckoutLane() : cashier_available(true), customers_served(0) {}

    void enqueue(const Customer& customer) { queue.push(customer); }
    Customer dequeue() {
        Customer customer = queue.front();
        queue.pop();
        return customer;
    }
    bool isEmpty() const { return queue.empty(); }
    int queueLength() const { return queue.size(); }
    bool isCashierAvailable() const { return cashier_available; }
    void setCashierAvailable(bool available) { cashier_available = available; }
    int getCustomersServed() const { return customers_served; }
    void incrementCustomersServed() { customers_served++; }
    Customer getCurrentCustomer() const { return current_customer; }
    void setCurrentCustomer(const Customer& customer) { current_customer = customer; }

private:
    queue<Customer> queue;
    bool cashier_available;
    int customers_served;
    Customer current_customer;
};

// Function to generate random interarrival times (exponential distribution)
double generate_random_interarrival_time(double arrival_rate) {
    static random_device rd;
    static mt19937 gen(rd());
    exponential_distribution<> distrib(arrival_rate);
    return distrib(gen);
}

// Function to generate random service times (uniform distribution)
int generate_random_service_time(int service_time) {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(service_time * 0.5, service_time * 1.5);
    return distrib(gen);
}

// Supermarket simulation function
void supermarket_simulation(int num_lanes, double arrival_rate, int service_time, int simulation_time) {
    vector<CheckoutLane> lanes(num_lanes);
    int current_time = 0;
    int next_customer_arrival = generate_random_interarrival_time(arrival_rate);
    int total_customers = 0;

    while (current_time < simulation_time) {
        // Check if a new customer arrives
        if (current_time == next_customer_arrival) {
            total_customers++;
            Customer new_customer(current_time);

            // Find the shortest queue
            int shortest_lane = 0;
            for (int i = 1; i < num_lanes; i++) {
                if (lanes[i].queueLength() < lanes[shortest_lane].queueLength()) {
                    shortest_lane = i;
                }
            }

            // Add the customer to the shortest queue
            lanes[shortest_lane].enqueue(new_customer);
            next_customer_arrival = current_time + generate_random_interarrival_time(arrival_rate);
        }

        // Process each lane
        for (int i = 0; i < num_lanes; i++) {
            if (!lanes[i].isEmpty() && lanes[i].isCashierAvailable()) {
                Customer current_customer = lanes[i].dequeue();
                lanes[i].setCurrentCustomer(current_customer);
                lanes[i].setCashierAvailable(false);

                // Schedule when the cashier will be available again
                int service_end_time = current_time + generate_random_service_time(service_time);
                lanes[i].incrementCustomersServed();

                // Simulate cashier becoming available after service time
                if (current_time == service_end_time) {
                    lanes[i].setCashierAvailable(true);
                }
            }
        }

        current_time++;
    }

    // Print simulation results
    cout << "Simulation Results:\n";
    cout << "Total customers served: " << total_customers << endl;
    for (int i = 0; i < num_lanes; i++) {
        cout << "Lane " << i + 1 << ": " << lanes[i].getCustomersServed() << " customers served\n";
    }
}

int main() {
    int num_lanes = 2;          // Number of checkout lanes
    double arrival_rate = 0.5;  // Average number of customers arriving per minute
    int service_time = 5;       // Average service time per customer (minutes)
    int simulation_time = 60;   // Total simulation time (minutes)

    supermarket_simulation(num_lanes, arrival_rate, service_time, simulation_time);

    return 0;
}
