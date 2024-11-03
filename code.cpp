#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

// Base class for fitness goals
class FitnessGoal {
public:
    virtual void suggestDiet(const string& gender) const = 0;
    virtual void suggestExercise(const string& gender) const = 0;
    virtual ~FitnessGoal() = default;
};

// Derived class for gaining weight
class GainProgram : public FitnessGoal {
public:
    void suggestDiet(const string& gender) const override {
        cout << "\n--- Suggested Diet Plan for " << gender << " (Goal: Gain) ---\n";
        cout << "1. Breakfast: Paneer paratha with curd (Approx. 650 calories)\n";
        cout << "2. Lunch: Chicken curry with rice and salad (Approx. 750 calories)\n";
        cout << "3. Dinner: Fish fry with dal and roti (Approx. 850 calories)\n";
        cout << "Total Daily Caloric Intake: Approx. 2500 calories\n";
        cout << "----------------------------------" << endl;
    }

    void suggestExercise(const string& gender) const override {
        cout << "\n--- Suggested Exercises for " << gender << " (Goal: Gain) ---\n";
        cout << "1. Weight training: upper body and lower body (4 times a week).\n";
        cout << "2. Core workouts: 3 times a week.\n";
        cout << "----------------------------------" << endl;
    }
};

// Derived class for losing weight
class LoseProgram : public FitnessGoal {
public:
    void suggestDiet(const string& gender) const override {
        cout << "\n--- Suggested Diet Plan for " << gender << " (Goal: Lose) ---\n";
        cout << "1. Breakfast: Oats with boiled egg (Approx. 350 calories)\n";
        cout << "2. Lunch: Grilled chicken salad with lemon dressing (Approx. 450 calories)\n";
        cout << "3. Dinner: Grilled fish with steamed vegetables (Approx. 550 calories)\n";
        cout << "Total Daily Caloric Intake: Approx. 1400 calories\n";
        cout << "----------------------------------" << endl;
    }

    void suggestExercise(const string& gender) const override {
        cout << "\n--- Suggested Exercises for " << gender << " (Goal: Lose) ---\n";
        cout << "1. Cardio: 30-45 minutes (5 times a week).\n";
        cout << (gender == "male" ? "2. Strength training: 3 times a week.\n" : "2. Pilates or yoga: 3 times a week.\n");
        cout << "----------------------------------" << endl;
    }
};

// Derived class for maintaining weight
class MaintainProgram : public FitnessGoal {
public:
    void suggestDiet(const string& gender) const override {
        cout << "\n--- Suggested Diet Plan for " << gender << " (Goal: Maintain) ---\n";
        cout << "1. Balanced meals with a mix of protein, carbs, and fats.\n";
        cout << "2. Snack on nuts and fruits throughout the day.\n";
        cout << "Total Daily Caloric Intake: Approx. 2000 calories (adjust as needed)\n";
        cout << "----------------------------------" << endl;
    }

    void suggestExercise(const string& gender) const override {
        cout << "\n--- Suggested Exercises for " << gender << " (Goal: Maintain) ---\n";
        cout << "1. Yoga: 3-4 times a week.\n";
        cout << "2. Walking: 30-60 minutes daily.\n";
        cout << "----------------------------------" << endl;
    }
};

class FitnessProgram {
public:
    void suggestProgram(const string& goal, const string& gender) {
        FitnessGoal* fitnessGoal = nullptr;

        if (goal == "gain") {
            fitnessGoal = new GainProgram();
        } else if (goal == "lose") {
            fitnessGoal = new LoseProgram();
        } else if (goal == "maintain") {
            fitnessGoal = new MaintainProgram();
        } else {
            cout << "Invalid goal.\n";
            return;
        }

        fitnessGoal->suggestDiet(gender);
        fitnessGoal->suggestExercise(gender);
        delete fitnessGoal; // Clean up
    }
};

class Person {
protected:
    string name;
    int age;
    float height;
    float weight;
    string gender;
public:
    void inputDetails() {
        cout << "Enter member name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter member age: ";
        cin >> age;
        cout << "Enter height(in cm): ";
        cin >> height;
        cout << "Enter weight(in kg): ";
        cin >> weight;
        cout << "Enter gender(male/female): ";
        cin >> gender;
    }
};

class Member : public Person {
private:
    int id;
    float bmi;
    string membershipStatus;
    string registrationDate;
    string expirationDate;
    float fee;

public:
    void inputMember(int memberId) {
        id = memberId;
        cout << "\n--- Member Registration ---\n";
        inputDetails();

        calculateBMI();

        cout << "enter registration date (YYYY-MM-DD): ";
        string date;
        cin.ignore();
        getline(cin, date);
        while (!isValidDate(date)){
            cout << "Invalid date format! Please enter a valid date (YYYY-MM-DD): ";
            getline(cin, date);
        }
        registrationDate = date;

        cout << "Choose subscription duration:\n";
        cout << "1. 1 month (₹1000)\n2. 3 months (₹2500)\n3. 6 months (₹5000)\n4. 1 year (₹10000)\n";
        int choice;
        cin >> choice;

        int monthsToAdd;
        switch (choice) {
            case 1: monthsToAdd = 1; fee = 1000; break;
            case 2: monthsToAdd = 3; fee = 2500; break;
            case 3: monthsToAdd = 6; fee = 5000; break;
            case 4: monthsToAdd = 12; fee = 10000; break;
            default: monthsToAdd = 1; fee = 1000;
        }

        expirationDate = addMonthsToDate(registrationDate,monthsToAdd);
        membershipStatus = "Active";

        cout << "Membership fee: ₹" << fee << endl;

        cout << "Do you want to gain, maintain, or lose weight? (Enter 'gain', 'maintain', 'lose'): ";
        string userGoal;
        cin >> userGoal;

        FitnessProgram fitness;
        fitness.suggestProgram(userGoal, gender);
    }

    void displayInfo() const {
        cout << "\n--- Member Information ---\n";
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender << endl;
        cout << "Height: " << height << " cm" << endl;
        cout << "Weight: " << weight << " kg" << endl;
        cout << fixed << setprecision(2) << "BMI: " << bmi << endl;
        cout << "Membership Status: " << membershipStatus << endl;
        cout << "Registration Date: " << registrationDate << endl;
        cout << "Expiration Date: " << expirationDate << endl;
        cout << "Membership Fee: ₹" << fee << endl;
    }

    void revoke(int monthsToRevoke) {
        expirationDate = addMonthsToDate(expirationDate, monthsToRevoke);
        membershipStatus = "Revoked for " + to_string(monthsToRevoke) + " months";
    }

private:
    void calculateBMI() {
        bmi = weight / ((height / 100) * (height / 100));
        suggestFitnessGoal();
    }

    void suggestFitnessGoal() const {
        string goal;
        if (bmi < 18.5) {
            goal = "gain weight/muscle";
        } else if (bmi >= 18.5 && bmi < 25) {
            goal = "maintain weight";
        } else {
            goal = "lose weight";
        }

        cout << "Your BMI is " << fixed << setprecision(2) << bmi << ".\nYou should aim to " << goal << ".\n";
    }

    string addMonthsToDate(const string& startDate, int monthsToAdd) {
        int year, month, day;
        sscanf(startDate.c_str(), "%d-%d-%d", &year, &month, &day);

        month += monthsToAdd;
        while (month > 12) {
            month -= 12;
            year++;
        }

        // Basic check for the number of days in the month
        int daysInMonth[] = { 31, (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        if (day > daysInMonth[month - 1]) {
            day = daysInMonth[month - 1]; // Set to last valid day of the month
        }

        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d", year, month, day);
        return string(buffer);
    }

    bool isValidDate(const string& date) const {
        int year, month, day;
        char dash1, dash2;
        istringstream ss(date);
        ss >> year >> dash1 >> month >> dash2 >> day;
        return !ss.fail() && ss.eof() && dash1 == '-' && dash2 == '-';
    }
};

int main() {
    const int MAX_MEMBERS = 100;
    Member members[MAX_MEMBERS];
    int memberCount = 0;
    int choice;

    do {
        cout << "\n--- Gym Membership System ---\n";
        cout << "1. Register New Member\n";
        cout << "2. Display All Members\n";
        cout << "3. Revoke Membership\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (memberCount < MAX_MEMBERS) {
                    members[memberCount].inputMember(memberCount + 1);
                    memberCount++;
                } else {
                    cout << "Maximum member limit reached.\n";
                }
                break;
            case 2:
                for (int i = 0; i < memberCount; i++) {
                    members[i].displayInfo();
                }
                break;
            case 3: {
                int memberId, monthsToRevoke;
                cout << "Enter member ID to revoke: ";
                cin >> memberId;
                cout << "Enter number of months to revoke: ";
                cin >> monthsToRevoke;
                if (memberId > 0 && memberId <= memberCount) {
                    members[memberId - 1].revoke(monthsToRevoke);
                    cout << "Membership revoked.\n";
                } else {
                    cout << "Invalid member ID.\n";
                }
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
