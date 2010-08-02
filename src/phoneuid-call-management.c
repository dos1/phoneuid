/*
 *  Copyright (C) 2009
 *      Authors (alphabetical) :
 *              Klaus 'mrmoku' Kurzmann <mok@fluxnetz.de>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Public License as published by
 *  the Free Software Foundation; version 2 of the license or any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser Public License for more details.
 */



#include <glib.h>
#include <glib-object.h>
#include <dbus/dbus-glib-bindings.h>
#include <phoneui/phoneui.h>

#include "phoneuid-dbus-common.h"
#include "phoneuid-call-management.h"
#include "phoneuid-call-management-service-glue.h"

G_DEFINE_TYPE(PhoneuidCallManagementService, phoneuid_call_management_service, G_TYPE_OBJECT)

static void
phoneuid_call_management_service_class_init(PhoneuidCallManagementServiceClass *klass)
{
	GError *error = NULL;

	/* Init the DBus connection, per-klass */
	klass->connection = dbus_g_bus_get (DBUS_BUS_SYSTEM, &error);
	if (klass->connection == NULL) {
		g_warning("Unable to connect to dbus: %s", error->message);
		g_error_free (error);
		return;
	}

	dbus_g_object_type_install_info (PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE,
			&dbus_glib_phoneuid_call_management_service_object_info);
}

static void
phoneuid_call_management_service_init(PhoneuidCallManagementService *object)
{
	PhoneuidCallManagementServiceClass *klass =
		PHONEUID_CALL_MANAGEMENT_SERVICE_GET_CLASS(object);

	/* Register DBUS path */
	dbus_g_connection_register_g_object(klass->connection,
			PHONEUID_CALL_MANAGEMENT_PATH,
			G_OBJECT (object));

}


PhoneuidCallManagementService *
phoneuid_call_management_service_new(void)
{
	return (g_object_new(PHONEUID_TYPE_CALL_MANAGEMENT_SERVICE, NULL));
}

gboolean
phoneuid_call_management_service_display_incoming(
		PhoneuidCallManagementService *object, const int call_id,
		const int status, const char *number,
		DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.CallManagement.DisplayIncoming");
	dbus_g_method_return(context);
	phoneui_incoming_call_show(call_id, status, number);
	return (TRUE);
}

gboolean
phoneuid_call_management_service_hide_incoming(
		PhoneuidCallManagementService *object, const gint call_id,
		DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.CallManagement.HideIncoming");
	dbus_g_method_return(context);
	phoneui_incoming_call_hide(call_id);
	return (TRUE);
}


gboolean
phoneuid_call_management_service_display_outgoing(
		PhoneuidCallManagementService *object, const int call_id,
		const int status, const char *number,
		DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.CallManagement.DisplayOutgoing");
	dbus_g_method_return(context);
	phoneui_outgoing_call_show(call_id, status, number);
	return (TRUE);
}

gboolean
phoneuid_call_management_service_hide_outgoing(
		PhoneuidCallManagementService *object, const int call_id,
		DBusGMethodInvocation *context)
{
	(void) object;
	g_debug("org.shr.phoneuid.CallManagement.HideOutgoing");
	dbus_g_method_return(context);
	phoneui_outgoing_call_hide(call_id);
	return (TRUE);
}


