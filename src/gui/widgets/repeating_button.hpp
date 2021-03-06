/*
   Copyright (C) 2009 - 2016 by Mark de Wever <koraq@xs4all.nl>
   Part of the Battle for Wesnoth Project http://www.wesnoth.org/

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/

#ifndef GUI_WIDGETS_REPEATING_BUTTON_HPP_INCLUDED
#define GUI_WIDGETS_REPEATING_BUTTON_HPP_INCLUDED

#include "gui/widgets/control.hpp"
#include "gui/widgets/clickable.hpp"

#include "gui/core/widget_definition.hpp"
#include "gui/core/window_builder.hpp"

namespace gui2
{

// ------------ WIDGET -----------{

class trepeating_button : public tcontrol, public tclickable_
{
public:
	trepeating_button();
	~trepeating_button();

	/**
	 * Connects a signal handler for a left mouse button down.
	 *
	 * This event is triggered when the button is pressed and, as long as the
	 * button stays down, every x ms afterwards.
	 *
	 * @param signal              The signal to connect.
	 */
	void connect_signal_mouse_left_down(const event::tsignal_function& signal);

	/**
	 * Disconnects a signal handler for a left mouse button down.
	 *
	 * @param signal              The signal to disconnect (should be the same
	 *                            as send to the connect call.
	 */
	void
	disconnect_signal_mouse_left_down(const event::tsignal_function& signal);

	/***** ***** ***** ***** Inherited ***** ***** ***** *****/

	/** See @ref tcontrol::set_active. */
	virtual void set_active(const bool active) override;

	/** See @ref tcontrol::get_active. */
	virtual bool get_active() const override;

	/** See @ref tcontrol::get_state. */
	virtual unsigned get_state() const override;

	/** Inherited from tclickable. */
	void connect_click_handler(const event::tsignal_function& signal)
	{
		connect_signal_mouse_left_down(signal);
	}

	/** Inherited from tclickable. */
	void disconnect_click_handler(const event::tsignal_function& signal)
	{
		disconnect_signal_mouse_left_down(signal);
	}

private:
	/**
	 * Possible states of the widget.
	 *
	 * Note the order of the states must be the same as defined in settings.hpp.
	 */
	enum tstate {
		ENABLED,
		DISABLED,
		PRESSED,
		FOCUSED,
		COUNT
	};

	void set_state(const tstate state);
	/**
	 * Current state of the widget.
	 *
	 * The state of the widget determines what to render and how the widget
	 * reacts to certain 'events'.
	 */
	tstate state_;

	/** The timer for the repeating events. */
	size_t repeat_timer_;

	/** See @ref tcontrol::get_control_type. */
	virtual const std::string& get_control_type() const override;

	/***** ***** ***** signal handlers ***** ****** *****/

	void signal_handler_mouse_enter(const event::tevent event, bool& handled);

	void signal_handler_mouse_leave(const event::tevent event, bool& handled);

	void signal_handler_left_button_down(const event::tevent event,
										 bool& handled);

	void signal_handler_left_button_up(const event::tevent event,
									   bool& handled);
};

// }---------- DEFINITION ---------{

struct trepeating_button_definition : public tcontrol_definition
{
	explicit trepeating_button_definition(const config& cfg);

	struct tresolution : public tresolution_definition_
	{
		explicit tresolution(const config& cfg);
	};
};

// }---------- BUILDER -----------{

namespace implementation
{

struct tbuilder_repeating_button : public tbuilder_control
{
public:
	explicit tbuilder_repeating_button(const config& cfg);

	using tbuilder_control::build;

	twidget* build() const;
};

} // namespace implementation

// }------------ END --------------

} // namespace gui2

#endif
