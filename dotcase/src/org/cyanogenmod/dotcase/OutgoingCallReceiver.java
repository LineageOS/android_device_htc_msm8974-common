/*
 * Copyright (c) 2015 The CyanogenMod Project
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * Also add information on how to contact you by electronic and paper mail.
 *
 */

package org.cyanogenmod.dotcase;

import org.cyanogenmod.dotcase.DotcaseStatus;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.database.Cursor;
import android.net.Uri;
import android.os.SystemClock;
import android.provider.ContactsContract;
import android.telephony.TelephonyManager;
import android.util.Log;

public class OutgoingCallReceiver extends BroadcastReceiver {
    private SharedPreferences mPrefs;

    @Override
    public void onReceive(Context context, Intent intent) {
        if (Intent.ACTION_NEW_OUTGOING_CALL.equals(intent.getAction())) {
            String number = intent.getStringExtra(Intent.EXTRA_PHONE_NUMBER);
            Uri uri = Uri.withAppendedPath(ContactsContract.PhoneLookup.CONTENT_FILTER_URI,
                    Uri.encode(number));
            Cursor cursor = context.getContentResolver().query(uri,
                    new String[] {ContactsContract.PhoneLookup.DISPLAY_NAME},
                    number, null, null);
            String name;
            if (cursor.moveToFirst()) {
                name = cursor.getString(cursor.getColumnIndex(
                        ContactsContract.PhoneLookup.DISPLAY_NAME));
            } else {
                name = "";
            }
            cursor.close();

            if (number.equalsIgnoreCase("restricted")) {
                // If call is restricted, don't show a number
                name = number;
                number = "";
            }

            name = CoverObserver.normalize(name);
            name = name + "  "; // Add spaces so the scroll effect looks good

            Dotcase.sStatus.setCallerInfo(name, number);
            Dotcase.sStatus.startInCall();
            Dotcase.sStatus.saveStatusPrefs(context);
        }
    }
}
