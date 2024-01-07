#include <DataTable.hpp>

std::vector<LogData> initializeLogData() {
    std::vector<LogData> data(Log::TypeCount);
    data[Log::Log1].speed = 185.f;
    data[Log::Log1].distanceBetweenLog = 420;
    data[Log::Log1].texture = Textures::Log1;
    data[Log::Log1].scaling = sf::Vector2f(0.5, 0.6);

    data[Log::Log2].speed = 170.f;
    data[Log::Log2].distanceBetweenLog = 550;
    data[Log::Log2].texture = Textures::Log1;
    data[Log::Log2].scaling = sf::Vector2f(0.8, 0.6);

    data[Log::SnowLog1].speed = 220.f;
    data[Log::SnowLog1].distanceBetweenLog = 470;
    data[Log::SnowLog1].texture = Textures::SnowLog1;
    data[Log::SnowLog1].scaling = sf::Vector2f(1.15, 1.0);

    data[Log::SnowLog2].speed = 200.f;
    data[Log::SnowLog2].distanceBetweenLog = 540;
    data[Log::SnowLog2].texture = Textures::SnowLog2;
    data[Log::SnowLog2].scaling = sf::Vector2f(1.25, 1.0);

    data[Log::Crocodile].speed = 60.f;
    data[Log::Crocodile].texture = Textures::Log;
    return data;
}
std::vector<ObstacleData> initializeObstacleData() {
    std::vector<ObstacleData> data(Obstacle::TypeCount);
    data[Obstacle::Tree1].dmg = 0;
    data[Obstacle::Tree1].speed = 0.f;
    data[Obstacle::Tree1].texture = Textures::Tree1;
    data[Obstacle::Tree1].scaling = sf::Vector2f(0.6, 0.6);
    data[Obstacle::Tree1].numOfFrames = 1;
    data[Obstacle::Tree1].pictureWidth = 270;
    data[Obstacle::Tree1].pictureHeight = 270;
    data[Obstacle::Tree1].collisionEffect = SoundEffect::Tree;

    data[Obstacle::Tree2].dmg = 0;
    data[Obstacle::Tree2].speed = 0.f;
    data[Obstacle::Tree2].texture = Textures::Tree2;
    data[Obstacle::Tree2].scaling = sf::Vector2f(0.9, 0.9);
    data[Obstacle::Tree2].numOfFrames = 1;
    data[Obstacle::Tree2].pictureWidth = 308;
    data[Obstacle::Tree2].pictureHeight = 456;
    data[Obstacle::Tree2].collisionEffect = SoundEffect::Tree;

    data[Obstacle::Tree3].dmg = 0;
    data[Obstacle::Tree3].speed = 0.f;
    data[Obstacle::Tree3].texture = Textures::Tree3;
    data[Obstacle::Tree3].scaling = sf::Vector2f(0.5, 0.5);
    data[Obstacle::Tree3].numOfFrames = 1;
    data[Obstacle::Tree3].pictureWidth = 188;
    data[Obstacle::Tree3].pictureHeight = 222;
    data[Obstacle::Tree3].collisionEffect = SoundEffect::Tree;

    data[Obstacle::Rock1].dmg = 0;
    data[Obstacle::Rock1].speed = 0.f;
    data[Obstacle::Rock1].texture = Textures::Rock1;
    data[Obstacle::Rock1].scaling = sf::Vector2f(0.35, 0.35);
    data[Obstacle::Rock1].numOfFrames = 1;
    data[Obstacle::Rock1].pictureWidth = 210;
    data[Obstacle::Rock1].pictureHeight = 208;
    data[Obstacle::Rock1].collisionEffect = SoundEffect::Rock;

    data[Obstacle::Rock2].dmg = 0;
    data[Obstacle::Rock2].speed = 0.f;
    data[Obstacle::Rock2].texture = Textures::Rock2;
    data[Obstacle::Rock2].scaling = sf::Vector2f(0.5, 0.5);
    data[Obstacle::Rock2].numOfFrames = 1;
    data[Obstacle::Rock2].pictureWidth = 148;   
    data[Obstacle::Rock2].pictureHeight = 176;
    data[Obstacle::Rock2].collisionEffect = SoundEffect::Rock;

    data[Obstacle::Ruin1].dmg = 0;
    data[Obstacle::Ruin1].speed = 0.f;
    data[Obstacle::Ruin1].texture = Textures::Ruin1;
    data[Obstacle::Ruin1].scaling = sf::Vector2f(0.5, 0.5);
    data[Obstacle::Ruin1].numOfFrames = 1;
    data[Obstacle::Ruin1].pictureWidth = 160;   
    data[Obstacle::Ruin1].pictureHeight = 186;
    data[Obstacle::Ruin1].collisionEffect = SoundEffect::Rock;

    data[Obstacle::Ruin1].dmg = 0;
    data[Obstacle::Ruin2].speed = 0.f;
    data[Obstacle::Ruin2].texture = Textures::Ruin2;
    data[Obstacle::Ruin2].scaling = sf::Vector2f(0.5, 0.5);
    data[Obstacle::Ruin2].numOfFrames = 1;
    data[Obstacle::Ruin2].pictureWidth = 200;   
    data[Obstacle::Ruin2].pictureHeight = 182;
    data[Obstacle::Ruin2].collisionEffect = SoundEffect::Rock;


    data[Obstacle::Volcano].dmg = 5;
    data[Obstacle::Volcano].speed = 0.f;
    data[Obstacle::Volcano].texture = Textures::Vocalno;
    data[Obstacle::Volcano].scaling = sf::Vector2f(0.35, 0.35);
    data[Obstacle::Volcano].numOfFrames = 1;
    data[Obstacle::Volcano].pictureWidth = 280;   
    data[Obstacle::Volcano].pictureHeight = 269;
    data[Obstacle::Volcano].collisionEffect = SoundEffect::Volcano;

    data[Obstacle::Fire].dmg = 5;
    data[Obstacle::Fire].speed = 0.f;
    data[Obstacle::Fire].texture = Textures::Fire;
    data[Obstacle::Fire].scaling = sf::Vector2f(1, 0.8);
    data[Obstacle::Fire].numOfFrames = 7;
    data[Obstacle::Fire].pictureWidth = 667;   
    data[Obstacle::Fire].pictureHeight = 205;
    data[Obstacle::Fire].collisionEffect = SoundEffect::Volcano;

    data[Obstacle::SnowTree].dmg = 5;
    data[Obstacle::SnowTree].speed = 0.f;
    data[Obstacle::SnowTree].texture = Textures::SnowTree;
    data[Obstacle::SnowTree].scaling = sf::Vector2f(0.35, 0.35);
    data[Obstacle::SnowTree].numOfFrames = 1;
    data[Obstacle::SnowTree].pictureWidth = 338;   
    data[Obstacle::SnowTree].pictureHeight = 322;
    data[Obstacle::SnowTree].deltaHeightBound = 15;
    data[Obstacle::SnowTree].collisionEffect = SoundEffect::Tree;

    data[Obstacle::SnowTree1].dmg = 5;
    data[Obstacle::SnowTree1].speed = 0.f;
    data[Obstacle::SnowTree1].texture = Textures::SnowTree1;
    data[Obstacle::SnowTree1].scaling = sf::Vector2f(0.52, 0.45);
    data[Obstacle::SnowTree1].numOfFrames = 1;
    data[Obstacle::SnowTree1].pictureWidth = 201;   
    data[Obstacle::SnowTree1].pictureHeight = 265;
    data[Obstacle::SnowTree1].deltaHeightBound = 15;
    data[Obstacle::SnowTree1].collisionEffect = SoundEffect::Tree;

    data[Obstacle::SnowMan].dmg = 5;
    data[Obstacle::SnowMan].speed = 0.f;
    data[Obstacle::SnowMan].texture = Textures::SnowMan;
    data[Obstacle::SnowMan].scaling = sf::Vector2f(0.52, 0.55);
    data[Obstacle::SnowMan].numOfFrames = 1;
    data[Obstacle::SnowMan].pictureWidth = 157;  
    data[Obstacle::SnowMan].pictureHeight = 176;
    data[Obstacle::SnowMan].deltaHeightBound = 15;
    data[Obstacle::SnowMan].collisionEffect = SoundEffect::SnowMan;

    data[Obstacle::Coin].dmg = 0;
    data[Obstacle::Coin].speed = 0.f;
    data[Obstacle::Coin].texture = Textures::Coin;
    data[Obstacle::Coin].scaling = sf::Vector2f(0.1, 0.1);
    data[Obstacle::Coin].numOfFrames = 6;
    data[Obstacle::Coin].pictureWidth = 3878;
    data[Obstacle::Coin].pictureHeight = 707;
    data[Obstacle::Coin].deltaHeightBound = 15;
    data[Obstacle::Coin].collisionEffect = SoundEffect::Coin;
    return data;
}

std::vector<AnimalData> initializeAnimalData(){
    std::vector<AnimalData> data(Animal::TypeCount);
    data[Animal::Elephant].dmg = 35;
    data[Animal::Elephant].speed = 200.f;
    data[Animal::Elephant].distanceBetweenAnimal = 600;
    data[Animal::Elephant].texture = Textures::Elephant;
    data[Animal::Elephant].scaling = sf::Vector2f(1.25, 1.25);
    data[Animal::Elephant].numOfFrames = 3;
    data[Animal::Elephant].pictureWidth = 288;
    data[Animal::Elephant].pictureHeight = 79;
    data[Animal::Elephant].duration = 1;
    data[Animal::Elephant].collisionEffect = SoundEffect::Elephant;

    data[Animal::Cow].dmg = 20;
    data[Animal::Cow].speed = 120.f;
    data[Animal::Cow].distanceBetweenAnimal = 500;
    data[Animal::Cow].texture = Textures::Cow;
    data[Animal::Cow].scaling = sf::Vector2f(0.35, 0.35);
    data[Animal::Cow].numOfFrames = 4;
    data[Animal::Cow].pictureWidth = 1075;
    data[Animal::Cow].pictureHeight = 191;
    data[Animal::Cow].duration = 1;
    data[Animal::Cow].collisionEffect = SoundEffect::Cow;

    data[Animal::Small_Dragon].dmg = 30;
    data[Animal::Small_Dragon].speed = 500.f;
    data[Animal::Small_Dragon].distanceBetweenAnimal = 900;
    data[Animal::Small_Dragon].texture = Textures::Small_Dragon;
    data[Animal::Small_Dragon].scaling = sf::Vector2f(1.5, 1.5);
    data[Animal::Small_Dragon].numOfFrames = 3;
    data[Animal::Small_Dragon].pictureWidth = 192;
    data[Animal::Small_Dragon].pictureHeight = 66;
    data[Animal::Small_Dragon].duration = 0.55;
    data[Animal::Small_Dragon].deltaHeightBound = 20;
    data[Animal::Small_Dragon].collisionEffect = SoundEffect::Dragon;

    data[Animal::Green_Dragon].dmg = 35;
    data[Animal::Green_Dragon].speed = 240.f;
    data[Animal::Green_Dragon].distanceBetweenAnimal = 700;
    data[Animal::Green_Dragon].texture = Textures::Green_Dragon;
    data[Animal::Green_Dragon].scaling = sf::Vector2f(1.42, 1.42);
    data[Animal::Green_Dragon].numOfFrames = 3;
    data[Animal::Green_Dragon].pictureWidth = 365;
    data[Animal::Green_Dragon].pictureHeight = 96;
    data[Animal::Green_Dragon].duration = 0.7;
    data[Animal::Green_Dragon].deltaWidthBound = 20;
    data[Animal::Green_Dragon].deltaHeightBound = 20;
    data[Animal::Green_Dragon].deltaLeftBound = 10;
    data[Animal::Green_Dragon].collisionEffect = SoundEffect::Dragon;

    data[Animal::Red_Dragon].dmg = 40;
    data[Animal::Red_Dragon].speed = 270.f;
    data[Animal::Red_Dragon].distanceBetweenAnimal = 700;
    data[Animal::Red_Dragon].texture = Textures::Red_Dragon;
    data[Animal::Red_Dragon].scaling = sf::Vector2f(1.4, 1.3);
    data[Animal::Red_Dragon].numOfFrames = 3;
    data[Animal::Red_Dragon].pictureWidth = 432;
    data[Animal::Red_Dragon].pictureHeight = 96;
    data[Animal::Red_Dragon].duration = 0.65;
    data[Animal::Red_Dragon].deltaWidthBound = 35;
    data[Animal::Red_Dragon].deltaHeightBound = 20;
    data[Animal::Red_Dragon].deltaLeftBound = 13;
    data[Animal::Red_Dragon].collisionEffect = SoundEffect::Dragon;

    data[Animal::Blue_Twin_Head_Dragon].dmg = 45;
    data[Animal::Blue_Twin_Head_Dragon].speed = 220.f;
    data[Animal::Blue_Twin_Head_Dragon].distanceBetweenAnimal = 600;
    data[Animal::Blue_Twin_Head_Dragon].texture = Textures::Blue_Twin_Head_Dragon;
    data[Animal::Blue_Twin_Head_Dragon].scaling = sf::Vector2f(1.315, 1.315);
    data[Animal::Blue_Twin_Head_Dragon].numOfFrames = 3;
    data[Animal::Blue_Twin_Head_Dragon].pictureWidth = 432;
    data[Animal::Blue_Twin_Head_Dragon].pictureHeight = 94;
    data[Animal::Blue_Twin_Head_Dragon].duration = 0.65;
    data[Animal::Blue_Twin_Head_Dragon].deltaWidthBound = 30;
    data[Animal::Blue_Twin_Head_Dragon].deltaHeightBound = 20;
    data[Animal::Blue_Twin_Head_Dragon].deltaLeftBound = 15;
    data[Animal::Blue_Twin_Head_Dragon].collisionEffect = SoundEffect::Dragon;

    data[Animal::Monster1].dmg = 75;
    data[Animal::Monster1].speed = 180.f;
    data[Animal::Monster1].distanceBetweenAnimal = 800;
    data[Animal::Monster1].texture = Textures::Monster1;
    data[Animal::Monster1].scaling = sf::Vector2f(0.4, 0.3);
    data[Animal::Monster1].numOfFrames = 11;
    data[Animal::Monster1].pictureWidth = 4019;
    data[Animal::Monster1].pictureHeight = 394;  
    data[Animal::Monster1].duration = 1;
    data[Animal::Monster1].deltaWidthBound = 20;
    data[Animal::Monster1].deltaHeightBound = 20;
    data[Animal::Monster1].deltaLeftBound = 10;
    data[Animal::Monster1].collisionEffect = SoundEffect::Monster;

    data[Animal::Reindeer].dmg = 40;
    data[Animal::Reindeer].speed = 410.f;
    data[Animal::Reindeer].distanceBetweenAnimal = 1000;
    data[Animal::Reindeer].texture = Textures::Reindeer;
    data[Animal::Reindeer].scaling = sf::Vector2f(0.3, 0.2);
    data[Animal::Reindeer].numOfFrames = 12;
    data[Animal::Reindeer].pictureWidth = 6764;
    data[Animal::Reindeer].pictureHeight = 447;
    data[Animal::Reindeer].duration = 0.5;
    data[Animal::Reindeer].deltaHeightBound = 0;
    data[Animal::Reindeer].collisionEffect = SoundEffect::Reindeer;

    data[Animal::SnowBear].dmg = 35;
    data[Animal::SnowBear].speed = 400.f;
    data[Animal::SnowBear].distanceBetweenAnimal = 900;
    data[Animal::SnowBear].texture = Textures::SnowBear;
    data[Animal::SnowBear].scaling = sf::Vector2f(0.3, 0.2);
    data[Animal::SnowBear].numOfFrames = 14;
    data[Animal::SnowBear].pictureWidth = 9152;
    data[Animal::SnowBear].pictureHeight = 476;
    data[Animal::SnowBear].duration = 0.5;
    data[Animal::SnowBear].deltaHeightBound = 0;
    data[Animal::SnowBear].collisionEffect = SoundEffect::Bear;

    data[Animal::Penguin].dmg = 25;
    data[Animal::Penguin].speed = 160.f;
    data[Animal::Penguin].distanceBetweenAnimal = 290;
    data[Animal::Penguin].texture = Textures::Penguin1;
    data[Animal::Penguin].scaling = sf::Vector2f(0.13, 0.13);
    data[Animal::Penguin].numOfFrames = 6;
    data[Animal::Penguin].pictureWidth = 2909;
    data[Animal::Penguin].pictureHeight = 485; 
    data[Animal::Penguin].duration = 0.5;
    data[Animal::Penguin].deltaHeightBound = 0;
    data[Animal::Penguin].collisionEffect = SoundEffect::Penguin;

    data[Animal::Wolf].dmg = 35;
    data[Animal::Wolf].speed = 300.f;
    data[Animal::Wolf].distanceBetweenAnimal = 620;
    data[Animal::Wolf].texture = Textures::Wolf;
    data[Animal::Wolf].scaling = sf::Vector2f(0.1, 0.15);
    data[Animal::Wolf].numOfFrames = 8;
    data[Animal::Wolf].pictureWidth = 8823;
    data[Animal::Wolf].pictureHeight = 556;
    data[Animal::Wolf].duration = 0.5;
    data[Animal::Wolf].deltaHeightBound = 0;
    data[Animal::Wolf].collisionEffect = SoundEffect::Wolf;
    return data;
}

std::vector<VehicleData> initializeVehicleData(){
    std::vector<VehicleData> data(Vehicle::TypeCount);
    data[Vehicle::Truck].dmg = 35;
    data[Vehicle::Truck].speed = 320.f;
    data[Vehicle::Truck].distanceBetweenVehicle = 800;
    data[Vehicle::Truck].texture = Textures::Truck;
    data[Vehicle::Truck].scaling = sf::Vector2f(0.8, 0.8);
    data[Vehicle::Truck].collisionEffect = SoundEffect::Truck;
    
    data[Vehicle::BlueCar].dmg = 30;
    data[Vehicle::BlueCar].speed = 280.f;
    data[Vehicle::BlueCar].distanceBetweenVehicle = 600;
    data[Vehicle::BlueCar].texture = Textures::BlueCar;
    data[Vehicle::BlueCar].scaling = sf::Vector2f(1.2,1.2);
    data[Vehicle::BlueCar].collisionEffect = SoundEffect::Car;

    data[Vehicle::SmallCar].dmg = 10;
    data[Vehicle::SmallCar].speed = 230.f;
    data[Vehicle::SmallCar].distanceBetweenVehicle = 600;
    data[Vehicle::SmallCar].texture = Textures::SmallCar;
    data[Vehicle::SmallCar].scaling = sf::Vector2f(1.15,1.15);
    data[Vehicle::SmallCar].collisionEffect = SoundEffect::Car;

    data[Vehicle::Ambulance].dmg = 25;
    data[Vehicle::Ambulance].speed = 800.f;
    data[Vehicle::Ambulance].distanceBetweenVehicle = 1450;
    data[Vehicle::Ambulance].texture = Textures::Ambulance;
    data[Vehicle::Ambulance].scaling = sf::Vector2f(1.2,1.2);
    data[Vehicle::Ambulance].collisionEffect = SoundEffect::Ambulance;

    data[Vehicle::PoliceCar].dmg = 30;
    data[Vehicle::PoliceCar].speed = 900.f;
    data[Vehicle::PoliceCar].distanceBetweenVehicle = 1500;
    data[Vehicle::PoliceCar].texture = Textures::PoliceCar;
    data[Vehicle::PoliceCar].scaling = sf::Vector2f(0.25,0.25);
    data[Vehicle::PoliceCar].collisionEffect = SoundEffect::PoliceCar;

    data[Vehicle::YellowCar].dmg = 30;
    data[Vehicle::YellowCar].speed = 200.f;
    data[Vehicle::YellowCar].distanceBetweenVehicle = 520;
    data[Vehicle::YellowCar].texture = Textures::YellowCar;
    data[Vehicle::YellowCar].scaling = sf::Vector2f(1.1,1.1);
    data[Vehicle::YellowCar].collisionEffect = SoundEffect::Car;

    data[Vehicle::OldCar].dmg = 10;
    data[Vehicle::OldCar].speed = 100.f;
    data[Vehicle::OldCar].distanceBetweenVehicle = 400;
    data[Vehicle::OldCar].texture = Textures::OldCar;
    data[Vehicle::OldCar].scaling = sf::Vector2f(1.1,1.1);
    data[Vehicle::OldCar].collisionEffect = SoundEffect::OldCar;

    data[Vehicle::SuperCar].dmg = 40;
    data[Vehicle::SuperCar].speed = 700.f;
    data[Vehicle::SuperCar].distanceBetweenVehicle = 1000;
    data[Vehicle::SuperCar].texture = Textures::SuperCar;
    data[Vehicle::SuperCar].scaling = sf::Vector2f(1.2,1.2);
    data[Vehicle::SuperCar].collisionEffect = SoundEffect::Car;
    
    data[Vehicle::IceCreamTruck].dmg = 45;
    data[Vehicle::IceCreamTruck].speed = 500.f;
    data[Vehicle::IceCreamTruck].distanceBetweenVehicle = 750;
    data[Vehicle::IceCreamTruck].texture = Textures::IceCreamTruck;
    data[Vehicle::IceCreamTruck].scaling = sf::Vector2f(0.5,0.5);
    data[Vehicle::IceCreamTruck].collisionEffect = SoundEffect::IceCreamTruck;

    data[Vehicle::SantaClaus].dmg = 35;
    data[Vehicle::SantaClaus].speed = 350.f;
    data[Vehicle::SantaClaus].distanceBetweenVehicle = 600;
    data[Vehicle::SantaClaus].texture = Textures::SantaClaus;
    data[Vehicle::SantaClaus].scaling = sf::Vector2f(0.55,0.55);
    data[Vehicle::SantaClaus].collisionEffect = SoundEffect::SantaClaus;

    return data;
}

std::vector<TrainData> initializeTrainData(){
    std::vector<TrainData> data(Train::TypeCount);
    data[Train::Train1].speed = 1000.f;
    data[Train::Train1].texture = Textures::Train1;
    data[Train::Train1].scaling = sf::Vector2f(0.51, 0.51);
    data[Train::Train1].collisionEffect = SoundEffect::Train2;
    
    data[Train::SnowTrain].speed = 1000.f;
    data[Train::SnowTrain].texture = Textures::SnowTrain;
    data[Train::SnowTrain].scaling = sf::Vector2f(0.59, 0.59);
    data[Train::SnowTrain].collisionEffect = SoundEffect::Train2;
    
    data[Train::WoodTrain].speed = 1000.f;
    data[Train::WoodTrain].texture = Textures::WoodTrain;
    data[Train::WoodTrain].scaling = sf::Vector2f(0.66, 0.55);
    data[Train::WoodTrain].collisionEffect = SoundEffect::Train2;

    data[Train::LavaTrain].speed = 1100.f;
    data[Train::LavaTrain].texture = Textures::LavaTrain;
    data[Train::LavaTrain].scaling = sf::Vector2f(0.85, 0.85);
    data[Train::LavaTrain].collisionEffect = SoundEffect::Train1;

    data[Train::SantaTrain].speed = 1000.f;
    data[Train::SantaTrain].texture = Textures::SantaTrain;
    data[Train::SantaTrain].scaling = sf::Vector2f(0.5, 0.5);
    data[Train::SantaTrain].collisionEffect = SoundEffect::Train2;

    return data;
}
std::vector<DecoratorData> initializeDecoratorData() {
    std::vector<DecoratorData> data(Decorator::TypeCount);
    data[Decorator::DecoTree1].speed = 0.f;
    data[Decorator::DecoTree1].texture = Textures::DecoTree1;
    data[Decorator::DecoTree1].scaling = sf::Vector2f(0.4, 0.4);

    data[Decorator::DecoTree2].speed = 0.f;
    data[Decorator::DecoTree2].texture = Textures::DecoTree2;
    data[Decorator::DecoTree2].scaling = sf::Vector2f(1.0, 1.0);

    data[Decorator::DecoFlower1].speed = 0.f;
    data[Decorator::DecoFlower1].texture = Textures::DecoFlower1;
    data[Decorator::DecoFlower1].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::DecoFlower2].speed = 0.f;
    data[Decorator::DecoFlower2].texture = Textures::DecoFlower2;
    data[Decorator::DecoFlower2].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::DecoIce1].speed = 0.f;
    data[Decorator::DecoIce1].texture = Textures::DecoIce1;
    data[Decorator::DecoIce1].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::DecoSnow1].speed = 0.f;
    data[Decorator::DecoSnow1].texture = Textures::DecoSnow1;
    data[Decorator::DecoSnow1].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::DecoStone].speed = 0.f;
    data[Decorator::DecoStone].texture = Textures::DecoStone;
    data[Decorator::DecoStone].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::Skullcap1].speed = 0.f;
    data[Decorator::Skullcap1].texture = Textures::Skullcap1;
    data[Decorator::Skullcap1].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::Skullcap2].speed = 0.f;
    data[Decorator::Skullcap2].texture = Textures::Skullcap2;
    data[Decorator::Skullcap2].scaling = sf::Vector2f(0.7, 0.7);

    data[Decorator::DeadSign].speed = 0.f;
    data[Decorator::DeadSign].texture = Textures::DeadSign;
    data[Decorator::DeadSign].scaling = sf::Vector2f(0.3, 0.3);

    data[Decorator::Gemstone1].speed = 0.f;
    data[Decorator::Gemstone1].texture = Textures::Gemstone1;
    data[Decorator::Gemstone1].scaling = sf::Vector2f(0.2, 0.2);

    data[Decorator::Gemstone2].speed = 0.f;
    data[Decorator::Gemstone2].texture = Textures::Gemstone2;
    data[Decorator::Gemstone2].scaling = sf::Vector2f(0.2, 0.2);

    data[Decorator::Gemstone3].speed = 0.f;
    data[Decorator::Gemstone3].texture = Textures::Gemstone3;
    data[Decorator::Gemstone3].scaling = sf::Vector2f(0.2, 0.2);
    return data;
}

std::vector<CharData> initializeCharData() {
    std::vector<CharData> data(MainChar::TypeCount);
    data[MainChar::Player1].hitpoints = 100.f;
    data[MainChar::Player1].manapoints = 100.f;
    data[MainChar::Player1].speed = 250.f;
    data[MainChar::Player1].texture = Textures::Standing1;
    data[MainChar::Player1].restTexture = Textures::Rest1;
    data[MainChar::Player1].upTexture = Textures::Up1;
    data[MainChar::Player1].downTexture = Textures::Down1;
    data[MainChar::Player1].leftTexture = Textures::Left1;
    data[MainChar::Player1].rightTexture = Textures::Right1;
    data[MainChar::Player1].pictureHeight = 52;
    data[MainChar::Player1].pictureWidth = 256;
    data[MainChar::Player1].numOfFrames = 4;
    data[MainChar::Player1].timeEachFrameInGame = 0.6;
    data[MainChar::Player1].timeEachFrameInMenu = 1;
    data[MainChar::Player1].scaling = 1.5;
    data[MainChar::Player1].name = "RED";
    data[MainChar::Player1].deltaLeftBound = 10;
    data[MainChar::Player1].deltaWidthBound = 20;
    data[MainChar::Player1].Ability = "No special ability.";
    data[MainChar::Player1].price = 0;

    data[MainChar::Player2].hitpoints = 125.f;
    data[MainChar::Player2].manapoints = 100.f;
    data[MainChar::Player2].speed = 200.f;
    data[MainChar::Player2].texture = Textures::Standing2;
    data[MainChar::Player2].restTexture = Textures::Rest2;
    data[MainChar::Player2].upTexture = Textures::Up2;
    data[MainChar::Player2].downTexture = Textures::Down2;
    data[MainChar::Player2].leftTexture = Textures::Left2;
    data[MainChar::Player2].rightTexture = Textures::Right2;
    data[MainChar::Player2].pictureHeight = 54;
    data[MainChar::Player2].pictureWidth = 160;
    data[MainChar::Player2].numOfFrames = 3;
    data[MainChar::Player2].timeEachFrameInGame = 0.6;
    data[MainChar::Player2].timeEachFrameInMenu = 1;
    data[MainChar::Player2].scaling = 1.5;
    data[MainChar::Player2].name = "NURSE";
    data[MainChar::Player2].Ability = "Heal 20" + std::string("%") + " of\nyour max HP";
    data[MainChar::Player2].price = 50;

    data[MainChar::Player3].hitpoints = 100.f;
    data[MainChar::Player3].manapoints = 100.f;
    data[MainChar::Player3].speed = 200.f;
    data[MainChar::Player3].texture = Textures::Standing3;
    data[MainChar::Player3].restTexture = Textures::Rest3;
    data[MainChar::Player3].upTexture = Textures::Up3;
    data[MainChar::Player3].downTexture = Textures::Down3;
    data[MainChar::Player3].leftTexture = Textures::Left3;
    data[MainChar::Player3].rightTexture = Textures::Right3;
    data[MainChar::Player3].pictureHeight = 52;
    data[MainChar::Player3].pictureWidth = 292;
    data[MainChar::Player3].numOfFrames = 4;
    data[MainChar::Player3].timeEachFrameInGame = 0.6;    
    data[MainChar::Player3].timeEachFrameInMenu = 1;
    data[MainChar::Player3].scaling = 1.5;
    data[MainChar::Player3].name = "CAT GOD";
    data[MainChar::Player3].deltaLeftBound = 10;
    data[MainChar::Player3].deltaWidthBound = 20;
    data[MainChar::Player3].Ability = "Invulnerable in\n3 seconds.";
    data[MainChar::Player3].price = 100;

    data[MainChar::Player4].hitpoints = 150.f;
    data[MainChar::Player4].manapoints = 100.f;
    data[MainChar::Player4].speed = 250.f;
    data[MainChar::Player4].texture = Textures::Standing4;
    data[MainChar::Player4].restTexture = Textures::Rest4;
    data[MainChar::Player4].upTexture = Textures::Up4;
    data[MainChar::Player4].downTexture = Textures::Down4;
    data[MainChar::Player4].leftTexture = Textures::Left4;
    data[MainChar::Player4].rightTexture = Textures::Right4;
    data[MainChar::Player4].pictureHeight = 57;
    data[MainChar::Player4].pictureWidth = 272;
    data[MainChar::Player4].numOfFrames = 4;
    data[MainChar::Player4].timeEachFrameInGame = 0.6;
    data[MainChar::Player4].timeEachFrameInMenu = 1;
    data[MainChar::Player4].scaling = 1.5;
    data[MainChar::Player4].name = "SPEEDSTER";
    data[MainChar::Player4].deltaLeftBound = 5;
    data[MainChar::Player4].deltaWidthBound = 10;
    data[MainChar::Player4].Ability = "Accelerate your\nspeed in 5 seconds.";
    data[MainChar::Player4].price = 200;

    data[MainChar::Player5].hitpoints = 200.f;
    data[MainChar::Player5].manapoints = 100.f;
    data[MainChar::Player5].speed = 250.f;
    data[MainChar::Player5].texture = Textures::Standing5;
    data[MainChar::Player5].restTexture = Textures::Rest5;
    data[MainChar::Player5].upTexture = Textures::Up5;
    data[MainChar::Player5].downTexture = Textures::Down5;
    data[MainChar::Player5].leftTexture = Textures::Left5;
    data[MainChar::Player5].rightTexture = Textures::Right5;
    data[MainChar::Player5].pictureHeight = 58;
    data[MainChar::Player5].pictureWidth = 175;
    data[MainChar::Player5].numOfFrames = 3;
    data[MainChar::Player5].timeEachFrameInGame = 0.6;
    data[MainChar::Player5].timeEachFrameInMenu = 1;
    data[MainChar::Player5].scaling = 1.5;
    data[MainChar::Player5].name = "GOD OF DESTRUCTION";
    data[MainChar::Player5].deltaLeftBound = 5;
    data[MainChar::Player5].deltaWidthBound = 10;
    data[MainChar::Player5].Ability = "Invulnerable and\naccelerate your speed\nin 5 seconds.";
    data[MainChar::Player5].price = 500;

    return data;
}

std::vector<RiverData> initializeRiverData(){
    std::vector<RiverData> data(River::TypeCount);
    data[River::WaterRiver].texture = Textures::River;
    data[River::WaterRiver].numOfFrames = 4;
    data[River::WaterRiver].pictureWidth = 7024;
    data[River::WaterRiver].pictureHeight = 100;

    data[River::LavaRiver].texture = Textures::LavaRiver;
    data[River::LavaRiver].numOfFrames = 4;
    data[River::LavaRiver].pictureWidth = 8218;
    data[River::LavaRiver].pictureHeight = 100;
    
    data[River::SnowRiver].texture = Textures::SnowRiver;
    data[River::SnowRiver].numOfFrames = 5;
    data[River::SnowRiver].pictureWidth = 8512;
    data[River::SnowRiver].pictureHeight = 100;
    return data;
}