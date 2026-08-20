//
// Created by Dmytrenko Kyrylo on 20.08.2026.
//



#ifndef PROGRAMMING_QT_GAME_H
#define PROGRAMMING_QT_GAME_H
#include <iostream>
#include <vector>
#include <span>
#include <set>

    struct Room;

    struct Enemy;
    struct Mortal;
    struct Game;
    struct Antagonist;
    struct Wumpus;
    struct Pit;
    struct Bat;



    struct Room {
        int number_this = -1;
        Room* next_1 = nullptr;
        Room* next_2 = nullptr;
        Room* next_3 = nullptr;
    };

    struct Enemy {
        virtual ~Enemy() = default;

        [[nodiscard]] virtual bool is_alive() const = 0;
        virtual bool is_current_location(const Room*) const = 0;
        [[nodiscard]] virtual std::string get_message_preview() const = 0;
        virtual void contact_with_antagonist(Antagonist*antagonist, const Room *wumpus_room, const Game *engine) const = 0;
    };

    constexpr Room hell_room = Room{666};


    void init_map(std::vector<Room>&);

    struct Mortal {
        virtual ~Mortal() = default;

        virtual void die() = 0;
        virtual const Room* get_location() = 0;
    };



    struct Pit : Enemy {
        Pit (const Room& loc) : location(loc){};

        [[nodiscard]] bool is_alive() const override {return true;}
        bool is_current_location(const Room* room) const override { return &location == room;};
        [[nodiscard]] std::string get_message_preview() const override {return "I feel a draft!";}
        void contact_with_antagonist(Antagonist*antagonist, const Room *wumpus_room, const Game *engine) const override;


        const Room& location;
    };

    struct Bat : Mortal, Enemy{
        Bat (const Room& loc) : location(&loc){};


        [[nodiscard]] const Room* get_location() override { return location;}
        void die() override;

        [[nodiscard]] bool is_alive() const override {return location != &hell_room;}
        bool is_current_location(const Room* room) const override {return location == room;}
        [[nodiscard]] std::string get_message_preview() const override {return "Bats nearby!";}
        void contact_with_antagonist(Antagonist*antagonist, const Room *wumpus_room, const Game *engine) const override;

        const Room* location;
    };

    struct Wumpus : Mortal, Enemy{
        Wumpus(const Room& loc) : location(&loc){}

        void move(); // random move on 1 step in range from 3 connected rooms


        void die() override;
        [[nodiscard]] const Room* get_location() override { return location;}

        [[nodiscard]] bool is_alive() const override {return location != &hell_room;}
        bool is_current_location(const Room* room) const override {return location == room;};
        [[nodiscard]] std::string get_message_preview() const override {return "I smell a Wumpus!";}
        void contact_with_antagonist(Antagonist*antagonist, const Room *wumpus_room, const Game *engine) const override;

        const Room *location;

    };

    struct Antagonist : Mortal{
        Antagonist(const Room& loc) : location(&loc){}

        [[nodiscard]] bool is_alive() const {return location != &hell_room;}

        void die() override;
        [[nodiscard]] const Room* get_location() override { return location;}

        void shoot(std::span<int> trajectory,const std::vector<Mortal*>& mobs);
        bool move(int next_room);
        void bat_move(const Room* wumpus_room, const Game* engine, int depth = 1);

        int arrows_capacity = 5;
        const Room* location;
    };


    struct Game {
        Game();
        void play();

        [[nodiscard]] std::vector<const Enemy *> get_list_of_alive_enemies() const;

    private:
        void init_bats(std::set<int>& sibel_values, int count = 2);
        void init_pits(std::set<int>& sibel_values, int count = 2);
        void init_wumpus(std::set<int>& sibel_values);
        void init_antagonist(std::set<int>& sibel_values);
        std::vector<Mortal*> get_alive_mobs();

        std::set<std::string> get_next_rooms_info_from_antagonist();


        std::vector<Room> map{20};

        std::vector<Pit> pits;
        std::vector<Bat> bats;
        Wumpus* wumpus = nullptr;
        Antagonist* antagonist = nullptr;

        void shoot_antagonist();
        void move_antagonist() const;
        void after_move_antagonist() const; // change loc or die antagonist or nothing (wumpus, bat, pit)




    };






#endif //PROGRAMMING_QT_GAME_H
