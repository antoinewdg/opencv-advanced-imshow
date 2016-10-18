//
// Created by antoinewdg on 10/18/16.
//

#ifndef COPY_MOVE_DETECTOR_IMAGE_VIEW_H
#define COPY_MOVE_DETECTOR_IMAGE_VIEW_H

#include <opencv2/core/core.hpp>

#include <SFML/Graphics.hpp>

#include "rgba_transformer.h"
#include "zoom_manager.h"
#include "drag_manager.h"
#include "ui_manager.h"
#include "rect_select_manager.h"

namespace oai {

    using cv::Mat_;
    using cv::Vec3b;
    using cv::Vec4b;


    class ImageView {
    public:
        template<class T>
        ImageView(Mat_<T> image);

        void display();

        void on_key_pressed(const sf::Event::KeyEvent &key_e) {
            m_ui_manager.on_key_pressed(key_e);
            if (key_e.code == sf::Keyboard::Space) {
                m_window.close();
            }
        }

        void on_mouse_wheel_scroll(const sf::Event::MouseWheelScrollEvent &scroll_e) {
            if (scroll_e.wheel == sf::Mouse::VerticalWheel) {
                m_zoom_manager.on_mouse_wheel_scroll_up(scroll_e);
            }
        }

        void on_mouse_button_released(const sf::Event::MouseButtonEvent &button_e) {
            if (button_e.button == sf::Mouse::Left) {
                m_drag_manager.on_mouse_left_released(button_e);
            } else if (button_e.button == sf::Mouse::Right) {
                m_select_manager.on_mouse_right_released(button_e);
            }
        }

        void on_mouse_button_pressed(const sf::Event::MouseButtonEvent &button_e) {
            if (button_e.button == sf::Mouse::Left) {
                m_drag_manager.on_mouse_left_pressed(button_e);
                m_ui_manager.on_mouse_left_pressed(button_e);
            } else if (button_e.button == sf::Mouse::Right) {
                m_select_manager.on_mouse_right_pressed(button_e);
            }
        }

        void on_mouse_move(const sf::Event::MouseMoveEvent &move_e) {
            m_drag_manager.on_mouse_move(move_e);
            m_select_manager.on_mouse_move(move_e);
        }

    private:
        Mat_<Vec4b> m_img;
        sf::Texture m_img_texture;
        sf::RenderWindow m_window;
        DragManager m_drag_manager;
        ZoomManager m_zoom_manager;
        UiManager m_ui_manager;
        RectSelectManager m_select_manager;

        sf::View m_image_view, m_ui_view;


    };

    template<class T>
    ImageView::ImageView(cv::Mat_<T> image):
            m_window(sf::VideoMode(image.cols, image.rows), "Image view"),
            m_drag_manager(m_window, m_image_view),
            m_zoom_manager(m_window, m_image_view),
            m_ui_view(m_window.getDefaultView()),
            m_ui_manager(m_window, m_image_view, std::cout),
            m_select_manager(m_window, m_image_view, std::cout) {

        m_img = RGBATransformer<T>::to_rgba(image);
        m_img_texture.create(m_img.cols, m_img.rows);
        m_img_texture.update(m_img.data);
        auto s = sf::Vector2i(m_window.getSize()) - sf::Vector2i(m_img.cols, m_img.rows);
        if (s.x > 0 && s.y > 0) {
            m_image_view.move(-sf::Vector2f(s/2));
        }
    }

    void ImageView::display() {

        sf::Sprite sprite(m_img_texture);
        while (m_window.isOpen()) {
            // check all the m_window's events that were triggered since the last iteration of the loop
            sf::Event event;


            while (m_window.pollEvent(event)) {
                // "close requested" event: we close the m_window
                typedef sf::Event E;
                switch (event.type) {

                    case E::MouseMoved:
                        on_mouse_move(event.mouseMove);
                        break;

                    case E::KeyPressed:
                        on_key_pressed(event.key);
                        break;

                    case E::MouseButtonPressed:
                        on_mouse_button_pressed(event.mouseButton);
                        break;

                    case E::MouseButtonReleased:
                        on_mouse_button_released(event.mouseButton);
                        break;

                    case E::MouseWheelScrolled:
                        on_mouse_wheel_scroll(event.mouseWheelScroll);
                        break;

                    case E::Closed:
                        m_window.close();
                        break;

                    default:
                        break;
                }
            }

            m_window.clear(sf::Color(0, 0, 0));
            m_window.setView(m_image_view);
            m_window.draw(sprite);
            m_select_manager.draw(m_window);

            m_window.setView(m_ui_view);
            m_ui_manager.draw();

            m_window.display();
        }
    }


}

#endif //COPY_MOVE_DETECTOR_IMAGE_VIEW_H
