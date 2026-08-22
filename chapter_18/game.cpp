//
// Created by Dmytrenko Kyrylo on 20.08.2026.
//

#include "game.h"
#include <random>
#include "./PPP/error.h"
#include <sstream>

namespace ch18::game
{
    void print_numbers_of_vector_rooms(std::vector<const Room*>& rooms) {
        for (auto& el : rooms) {
            std::cout << el->number_this << ' ';
        }
        std::cout << std::endl;
    }

    std::default_random_engine& get_rand()
    {
        static std::default_random_engine ran;
        return ran;
    };

    void seed(int s) { get_rand().seed(s); }
    void seed() { get_rand().seed(); }
    inline int random_int(int min, int max) { return std::uniform_int_distribution<>{min, max}(get_rand()); }

    inline int random_int(int max) { return random_int(0, max); }

    std::set<int> get_set_range(const std::pair<int,int>& min_max = {1,20}) {
        std::set<int> result;
        for (int i = min_max.first-1; i < min_max.second; ++i) {
            result.insert(i+1);
        }

        return result;
    }

    int get_random_value_in_set(const std::set<int>& sibel_values, const std::pair<int,int>& min_max = {1,20}) {
        int result_random = random_int(min_max.first,min_max.second);
        int val_left = result_random-1;
        int val_right = result_random+1;
        while (!sibel_values.contains(result_random)) {
            if (sibel_values.contains(val_left)) {
                result_random = val_left;
                break;
            }

            if (sibel_values.contains(val_right)) {
                result_random = val_right;
                break;
            }

            --val_left;
            ++val_right;
        }

        return result_random;
    }

    void init_numbers_of_map(std::vector<Room>& map) {
        auto set = get_set_range();
        for (auto& el: map) {
            int result_random = get_random_value_in_set(set);

            el.number_this = set.extract(result_random).value();

        }
    }



    void init_map(std::vector<Room>& map) {
        map[0].next_1 = &map[1];    map[0].next_2 = &map[4];    map[0].next_3 = &map[7]; // 1
        map[1].next_1 = &map[0];    map[1].next_2 = &map[2];    map[1].next_3 = &map[9]; // 2
        map[2].next_1 = &map[1];    map[2].next_2 = &map[3];    map[2].next_3 = &map[11]; // 3
        map[3].next_1 = &map[13];    map[3].next_2 = &map[4];    map[3].next_3 = &map[2]; // 4
        map[4].next_1 = &map[0];    map[4].next_2 = &map[3];    map[4].next_3 = &map[5]; // 5
        map[5].next_1 = &map[14];    map[5].next_2 = &map[4];    map[5].next_3 = &map[6]; // 6
        map[6].next_1 = &map[16];    map[6].next_2 = &map[5];    map[6].next_3 = &map[7]; // 7
        map[7].next_1 = &map[6];    map[7].next_2 = &map[0];    map[7].next_3 = &map[8]; // 8
        map[8].next_1 = &map[17];    map[8].next_2 = &map[9];    map[8].next_3 = &map[7]; // 9
        map[9].next_1 = &map[10];    map[9].next_2 = &map[8];    map[9].next_3 = &map[1]; // 10
        map[10].next_1 = &map[18];    map[10].next_2 = &map[11];    map[10].next_3 = &map[9]; // 11
        map[11].next_1 = &map[12];    map[11].next_2 = &map[10];    map[11].next_3 = &map[2]; // 12
        map[12].next_1 = &map[11];    map[12].next_2 = &map[19];    map[12].next_3 = &map[13]; // 13
        map[13].next_1 = &map[14];    map[13].next_2 = &map[12];    map[13].next_3 = &map[3]; // 14
        map[14].next_1 = &map[13];    map[14].next_2 = &map[15];    map[14].next_3 = &map[5]; // 15
        map[15].next_1 = &map[14];    map[15].next_2 = &map[16];    map[15].next_3 = &map[19]; // 16
        map[16].next_1 = &map[15];    map[16].next_2 = &map[6];    map[16].next_3 = &map[17]; // 17
        map[17].next_1 = &map[16];    map[17].next_2 = &map[8];    map[17].next_3 = &map[18]; // 18
        map[18].next_1 = &map[10];    map[18].next_2 = &map[17];    map[18].next_3 = &map[19]; // 19
        map[19].next_1 = &map[12];    map[19].next_2 = &map[18];    map[19].next_3 = &map[15]; // 20

        init_numbers_of_map(map);

        return;
    }

    const Room& get_room_from_map_by_number(const int number, const std::vector<Room>& map) {
        for (const Room& room : map) {
            if (room.number_this == number)
                return room;
        }

        error("bad room number");
        return map.front();
    }

    void Game::init_bats(std::set<int> &sibel_values, const int count) {
        for (int i = 0; i < count; ++i) {
            int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
            const Room& room_for_bat = get_room_from_map_by_number(random_room_number,this->map);
            this->bats.emplace_back(room_for_bat);
        }

    }



    void Game::init_pits(std::set<int> &sibel_values, const int count) {
        for (int i = 0; i < count; ++i) {
            int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
            const Room& room_for_pit = get_room_from_map_by_number(random_room_number,this->map);
            this->pits.emplace_back(room_for_pit);
        }
    }

    void Game::init_wumpus(std::set<int> &sibel_values) {
        int random_room_number = sibel_values.extract(
                get_random_value_in_set(sibel_values)).value();
        const Room& room_for_wumpus = get_room_from_map_by_number(random_room_number,this->map);
        this->wumpus = new Wumpus{room_for_wumpus};
    }

    void Game::init_antagonist(std::set<int> &sibel_values) {
        int random_room_number = sibel_values.extract(
         get_random_value_in_set(sibel_values)).value();
        const Room& room_for_antagonist = get_room_from_map_by_number(random_room_number,this->map);
        this->antagonist = new Antagonist{room_for_antagonist};
    }

    std::vector<Mortal*> Game::get_alive_mobs() {
        std::vector<Mortal*> result;
        result.reserve(bats.size()+2);
        for (Mortal& bat : bats) {
            result.push_back(&bat);
        }

        result.push_back(antagonist);
        result.push_back(wumpus);

        // TODO must tested
        for (auto it = result.begin(); it != result.end();) // clean dead mobs
            if ((*it)->get_location() == &hell_room)
                result.erase(it);
            else
                ++it;


        return result;
    }


    void Pit::contact_with_antagonist(Antagonist *antagonist,
        const Room *wumpus_room, const Game *engine) const {
        antagonist->die();
        if (wumpus_room && engine)
            return;
    }

    void Bat::die() {
        location = &hell_room;
    }

    const Room* get_random_next_location(const Room* location) {
        const Room* result = nullptr;

        int choise = random_int(1,3);
        switch (choise) {
        case 1:
            result = location->next_1;
            break;

        case 2:
            result = location->next_2;
            break;

        case 3:
            result = location->next_3;
            break;

        default:
            error("bad random engine");

        }

        return result;
    }

    void Bat::contact_with_antagonist(Antagonist * antagonist, const Room *wumpus_room, const Game *engine) const {
        antagonist->bat_move(wumpus_room, engine);
    }

    void Wumpus::move() {
        location = get_random_next_location(location);
    }



    void Wumpus::die() {
        location = &hell_room;
    }


    const Room* get_next_room_from_number(int room_number, const Room* current_room) {
        std::vector<const Room*> available_rooms {
            current_room->next_1,
            current_room->next_2,
            current_room->next_3};

        for (const Room* true_room : available_rooms ) {
            if (true_room->number_this == room_number)
                return true_room;
        }

        return nullptr;
    }

    void kill_mobs_in_room(const std::vector<Mortal*>& mobs,const Room* room) {
        for (const auto mob : mobs) {
            if (room == mob->get_location())
                mob->die();
        }
    }

    void Antagonist::shoot(std::span<int> trajectory, const std::vector<Mortal*>& mobs){
        const Room* current_room = this->location;
        bool is_random = false;

        for (int room_number : trajectory) {
            const Room* prev = current_room;

            if (!is_random) current_room = get_next_room_from_number(room_number,current_room);

            if (current_room == nullptr || is_random) {
                is_random = true;
                current_room = get_random_next_location(prev);
            }

            kill_mobs_in_room(mobs,current_room);
        }

        --arrows_capacity;
    }

    bool Antagonist::move(int next_room) {
        bool result_operation = false;
        std::vector<const Room*> available_rooms {
            location->next_1,
            location->next_2,
            location->next_3};

        for (const Room* true_room : available_rooms ) {
            if (true_room->number_this == next_room) {
                location = true_room;
                result_operation = true;
                break;
            }
        }

        return result_operation;
    }

    void insert_room_range(const std::set<const Room *>& from,
        std::set<const Room *>& to)
    {
        for (const auto& room: from)
        {
            to.insert(room);
        }
    }

    std::set<const Room *> get_available_rooms_bat_moving(const Room *wumpus_room, const int depth) {
        std::set<const Room *> available_rooms    {wumpus_room,wumpus_room->next_1,
            wumpus_room->next_2,wumpus_room->next_3};
        std::set last_level {available_rooms};
        for (int i = 0; i < depth; ++i) {
            std::set<const Room *> next_level;
            for (const auto& room : last_level) {
                const auto & first = room->next_1;
                const auto & second = room->next_2;
                const auto & third = room->next_3;

                if (!available_rooms.contains(first)) next_level.emplace(first);
                if (!available_rooms.contains(second)) next_level.emplace(second);
                if (!available_rooms.contains(third)) next_level.emplace(third);
            }
            last_level = next_level;
            insert_room_range(last_level,available_rooms);
            // available_rooms.insert_range(last_level);
        }

        // available_rooms.extract(wumpus_room);

        return available_rooms;
    }

    const Room* get_random_room_from_set(const std::set<const Room *>& available_rooms ) {
        const int random_room = random_int(0,static_cast<int>(available_rooms.size()));
        int i = 0;

        for (const auto& room : available_rooms) {
            if (i == random_room) {
                return room;
            }
            ++i;
        }

        return nullptr;
    }

    void remove_rooms_with_enemies_from_set(const std::vector<const Enemy*>& enemies, std::set<const Room *>& rooms ) {
        std::vector<const Room*> rooms_for_extract;
        for (const Room* room : rooms)
            for (const Enemy* enemy : enemies)
                if (enemy->is_current_location(room))
                    rooms_for_extract.emplace_back(room);

        for (const Room* room : rooms_for_extract) // extract
            rooms.extract(room);
    }

    void Antagonist::bat_move(const Room *wumpus_room, const Game* engine, const int depth) {
        auto available_rooms = get_available_rooms_bat_moving(wumpus_room,depth);
        std::vector<const Enemy*> enemies = engine->get_list_of_alive_enemies();
        remove_rooms_with_enemies_from_set(enemies,available_rooms); // for legal moving

        location = get_random_room_from_set(available_rooms);
    }


    void Wumpus::contact_with_antagonist(Antagonist *antagonist, const Room *wumpus_room, const Game *engine) const {
        antagonist->die();
        if (wumpus_room && engine)
            return;
    }

    void Antagonist::die() {
        location = &hell_room;
    }

    Game::Game() {
        init_map(this->map);
        auto sibel_rooms_for_game_elements = get_set_range();

        init_pits(sibel_rooms_for_game_elements);
        init_bats(sibel_rooms_for_game_elements);
        init_antagonist(sibel_rooms_for_game_elements);
        init_wumpus(sibel_rooms_for_game_elements);

    }

    std::vector<const Enemy *> Game::get_list_of_alive_enemies() const {
        std::vector<const Enemy*> enemies;

        enemies.emplace_back(wumpus);
        for (const Enemy& bat : bats) {
            if (bat.is_alive())
                enemies.emplace_back(&bat);
        }
        for (const Enemy& pit : pits)
            enemies.emplace_back(&pit);

        return enemies;
    }

    std::set<std::string> Game::get_next_rooms_info_from_antagonist() {
        std::set<std::string> info;
        auto enemies = get_list_of_alive_enemies();

        std::vector next_rooms {antagonist->location->next_1,
            antagonist->location->next_2, antagonist->location->next_3};

        for (auto& room : next_rooms)
            for (const Enemy* enemy: enemies)
                if (enemy->is_current_location(room))
                    info.insert(enemy->get_message_preview());

        std::ostringstream info_about_locations ;
        info_about_locations << "Current location: " << antagonist->location->number_this << ", rooms around: ";

        for (auto& room : next_rooms)
            info_about_locations << room->number_this << " ";

        info.insert(info_about_locations.str());

        return info;
    }



    void print_info_about_next_rooms(const std::set<std::string>& info_about_enemies) {
        if (info_about_enemies.empty())
            std::cout << "No menaces around you.\n";

        for (auto& msg : info_about_enemies) {
            std::cout << msg << std::endl;
        }
    }

    void Game::play() {
        while (antagonist->is_alive() && wumpus->is_alive()) {
            std::cout << "Current capacity of your arrows: " << antagonist->arrows_capacity << std::endl;
            print_info_about_next_rooms(get_next_rooms_info_from_antagonist());

            std::cout << "What would you do? Enter 'm' if you want move, 's' if you want shoot: ";
            char answer = 0;
            std::cin >> answer;

            switch (answer) {
            case 'm':
                move_antagonist();
                after_move_antagonist(); // TODO see to Antagonist::bat_move
                break;

            case 's':
                shoot_antagonist();
                break;

            default:
                std::cout << "Bad answer!";
                continue;
            }


        }


    }

    void Game::shoot_antagonist() {
        if (antagonist->arrows_capacity == 0) {
            std::cout << "You can't shooting, capacity arrows is 0! But you can move)";
            return;
        }

        std::cout << "Shooting..." << std::endl
            << "Enter how much rooms arrow must reached (less then 5): ";

        int count_rooms_reaching;
        std::cin >> count_rooms_reaching;
        std::vector<int> trace(count_rooms_reaching);

        std::cout << "Inputting trace...";
        for (int i = 0; i < count_rooms_reaching; ++i) {
            std::cout << "Enter trace[" <<  i<< "]: ";
            std::cin >> trace[i];
            std::cout << std::endl;
        }

        antagonist->shoot(trace,get_alive_mobs());
    }



    void Game::move_antagonist() const {
        using namespace std;
        vector<const Room*> available_rooms {antagonist->location->next_1,  antagonist->location->next_2,
                antagonist->location->next_3};
        cout << "Next available rooms for moving: ";
        print_numbers_of_vector_rooms(available_rooms);

        cout << "Enter number of room for move: ";

        int input_number;
        cin >> input_number;
        while (!antagonist->move(input_number)){
            cout << "Bad input number! Please, enter rooms from this list: ";
            print_numbers_of_vector_rooms(available_rooms);
            cout << "Enter number of room for move: ";
            cin >> input_number;
        }

    }

    void Game::after_move_antagonist() const {
        auto enemies = get_list_of_alive_enemies();

        for (const Enemy* enemy : enemies)
            if (enemy->is_current_location(antagonist->location)) {
                enemy->contact_with_antagonist(antagonist,wumpus->location, this);
                break;
            }
    }

    int Game::get_antagonist_room_number()
    {
       return  antagonist->location->number_this;
    }

    std::vector<int> Game::get_next_antagonist_rooms()
    {
        std::vector<int> result;
        result.reserve(3);

        result.push_back(antagonist->location->next_1->number_this);
        result.push_back(antagonist->location->next_2->number_this);
        result.push_back(antagonist->location->next_3->number_this);

        return result;
    }
}

