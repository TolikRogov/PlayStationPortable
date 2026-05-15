#include "BotTank.hpp"
#include <cmath>

void BotTank::set_type(const BotType& type) {
    type_ = type;
    switch(type) {
        case BotType::easy: {
            this->set_health(10);
            this->set_speed(3);
            break;
        }

        case BotType::normal: {
            this->set_health(30);
            this->set_speed(5);
            break;
        }   

        case BotType::hard: {
            this->set_health(50);
            this->set_speed(3);
            break;
        }

        default: break;
    }
}

void BotTank::handle_movement() {
    
    unsigned long now = millis();
    
    // Принимаем решения
    if (now - last_decision_time_ > DECISION_INTERVAL) {
        make_decision();
        last_decision_time_ = now;
    }
}

void BotTank::make_decision() {
    if (wants_to_shoot()) {
        shoot();
    }

    if (get_valid_dir_callback_) {
        Rect current_rect = get_collision_rect();
        int speed = get_speed();
        
        std::vector<Direction> valid_dirs = get_valid_dir_callback_(speed, current_rect);
        
        if (!valid_dirs.empty()) {
            switch(type_) {
            case BotType::easy: {
                int random_index = rand() % valid_dirs.size();
                setOrientation(valid_dirs[random_index]);
                break;
            }
            
            case BotType::normal: {
                    // NORMAL: 70% двигаться к базе, 30% случайно
                    if ((rand() % 100) < 70) {
                        Direction toward_target = get_direction_toward_target();
                        // Проверяем, доступно ли направление к базе
                        if (std::find(valid_dirs.begin(), valid_dirs.end(), toward_target) != valid_dirs.end()) {
                            setOrientation(toward_target);
                        } else {
                            // Если направление к базе заблокировано - выбираем случайное
                            int random_index = rand() % valid_dirs.size();
                            setOrientation(valid_dirs[random_index]);
                        }
                    } else {

                        int random_index = rand() % valid_dirs.size();
                        setOrientation(valid_dirs[random_index]);
                    }
                    break;
                }

            case BotType::hard: {
                Direction toward_target = get_direction_toward_target();
                // Проверяем, доступно ли направление к базе
                if (std::find(valid_dirs.begin(), valid_dirs.end(), toward_target) != valid_dirs.end()) {
                    setOrientation(toward_target);
                } else {
                    // Если направление к базе заблокировано - выбираем случайное
                    int random_index = rand() % valid_dirs.size();
                    setOrientation(valid_dirs[random_index]);
                }
            }

            }
            
        }
    }
}

Direction BotTank::get_direction_toward_target() {
    int bot_center_x = getX() + getWidth() / 2;
    int bot_center_y = getY() + getHeight() / 2;
    
    int dx = 12*20 - bot_center_x;
    int dy = 15*20 - bot_center_y;
    
    if (abs(dx) > abs(dy)) {
        return (dx > 0) ? DIR_RIGHT : DIR_LEFT;
    } else {
        return (dy > 0) ? DIR_DOWN : DIR_UP;
    }
}

bool BotTank::wants_to_shoot() {
    if (!this->canShoot()) return false;
    
    unsigned long now = millis();
    if (now - last_shot_time_ < this->get_shoot_cooldown()*2) return false;
    
    // Просто стреляем с заданным интервалом, без проверки расстояния
    return true;
}