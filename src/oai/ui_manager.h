//
// Created by antoinewdg on 10/18/16.
//

#ifndef OPENCV_ADVANCED_IMSHOW_UI_MANAGER_H
#define OPENCV_ADVANCED_IMSHOW_UI_MANAGER_H

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace oai {
    /**
     * Display pixel coordinates on the UI
     *
     * For now not an UI at all, all output is made
     * one the terminal standard output. Prints the current
     * pixel coords on left click.
     */
    class UiManager {
    public:
        UiManager(sf::RenderWindow &window, const sf::View &image_view,
                  std::ostream &out, const cv::Mat_<Vec4b> &image) :
                m_window(window), m_image_view(image_view), m_out(out),
                m_image(image) {
        }

        void draw() {
        }

        inline void on_key_pressed(const sf::Event::KeyEvent &key_e) {
            if (key_e.code == sf::Keyboard::H) {
                _print_current_pixel();
            }
        }

        inline void on_mouse_left_pressed(const sf::Event::MouseButtonEvent &button_e) {
            _print_current_pixel();
        }


    private:

        inline void _print_current_pixel() {
            auto p = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window), m_image_view);
            int x = int(std::floor(p.x)), y = int(std::floor(p.y));
            m_out << x << ", " << y << ": " << m_image(y, x) << std::endl;
        }


        sf::RenderWindow &m_window;
        const sf::View &m_image_view;
        std::ostream &m_out;
        const cv::Mat_<Vec4b> &m_image;
    };
}
#endif //OPENCV_ADVANCED_IMSHOW_UI_MANAGER_H
