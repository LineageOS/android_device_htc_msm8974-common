/*
 * Copyright (C) 2018 The LineageOS Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.qualcomm.qti.internal.telephony;

import android.content.Context;
import android.os.ServiceManager;
import android.telephony.PhoneNumberUtils;

import org.codeaurora.internal.IDepersoResCallback;
import org.codeaurora.internal.IDsda;
import org.codeaurora.internal.IExtTelephony;

public class ExtTelephonyServiceImpl extends IExtTelephony.Stub {

    // Service name
    private static final String EXT_TELEPHONY_SERVICE_NAME = "extphone";

    // Intents (+ extras) to broadcast
    private static final String ACTION_UICC_MANUAL_PROVISION_STATUS_CHANGED =
            "org.codeaurora.intent.action.ACTION_UICC_MANUAL_PROVISION_STATUS_CHANGED";
    private static final String EXTRA_NEW_PROVISION_STATE = "newProvisionState";

    // UICC States
    private static final int PROVISIONED = 1;
    private static final int NOT_PROVISIONED = 0;
    private static final int INVALID_STATE = -1;
    private static final int CARD_NOT_PRESENT = -2;

    // Error codes
    private static final int SUCCESS = 0;
    private static final int GENERIC_FAILURE = -1;
    private static final int INVALID_INPUT = -2;
    private static final int BUSY = -3;

    private static Context sContext;
    private static ExtTelephonyServiceImpl sInstance;

    public static void init(Context context) {
        sContext = context;
        sInstance = getInstance();
    }

    public static ExtTelephonyServiceImpl getInstance() {
        if (sInstance == null) {
            sInstance = new ExtTelephonyServiceImpl();
        }

        return sInstance;
    }

    private ExtTelephonyServiceImpl() {
        if (ServiceManager.getService(EXT_TELEPHONY_SERVICE_NAME) == null) {
            ServiceManager.addService(EXT_TELEPHONY_SERVICE_NAME, this);
        }
    }

    @Override
    public int getCurrentUiccCardProvisioningStatus(int slotId) {
        return PROVISIONED;
    }

    @Override
    public int getUiccCardProvisioningUserPreference(int slotId) {
        return getCurrentUiccCardProvisioningStatus(slotId);
    }

    @Override
    public int activateUiccCard(int slotId) {
        return SUCCESS;
    }

    @Override
    public int deactivateUiccCard(int slotId) {
        return GENERIC_FAILURE;
    }

    @Override
    public boolean isSMSPromptEnabled() {
        return false;
    }

    @Override
    public void setSMSPromptEnabled(boolean enabled) {
        // Do nothing here
    }

    @Override
    public int getPhoneIdForECall() {
        return -1;
    }

    @Override
    public void setPrimaryCardOnSlot(int slotId) {
        // Do nothing here
    }

    @Override
    public boolean isFdnEnabled() {
        return false;
    }

    @Override
    public int getPrimaryStackPhoneId() {
        return -1;
    }

    @Override
    public boolean isEmergencyNumber(String number) {
        return PhoneNumberUtils.isEmergencyNumber(number);
    }

    @Override
    public boolean isLocalEmergencyNumber(String number) {
        return PhoneNumberUtils.isLocalEmergencyNumber(sContext, number);
    }

    @Override
    public boolean isPotentialEmergencyNumber(String number) {
        return PhoneNumberUtils.isPotentialEmergencyNumber(number);
    }

    @Override
    public boolean isPotentialLocalEmergencyNumber(String number) {
        return PhoneNumberUtils.isPotentialLocalEmergencyNumber(sContext, number);
    }

    @Override
    public boolean isDeviceInSingleStandby() {
        return false;
    }

    @Override
    public boolean setLocalCallHold(int subId, boolean enable) {
        return false;
    }

    @Override
    public void switchToActiveSub(int subId) {
        // Do nothing here
    }

    @Override
    public void setDsdaAdapter(IDsda dsdaAdapter) {
        // Do nothing here
    }

    @Override
    public int getActiveSubscription() {
        return -1;
    }

    @Override
    public boolean isDsdaEnabled() {
        return false;
    }

    @Override
    public void supplyIccDepersonalization(String netpin, String type,
            IDepersoResCallback callback, int phoneId) {
        // Do nothing here
    }

    @Override
    public int getPrimaryCarrierSlotId() {
        return -1;
    }

    @Override
    public boolean isPrimaryCarrierSlotId(int slotId) {
        return false;
    }

    @Override
    public boolean setSmscAddress(int slotId, String smsc) {
        return false;
    }

    @Override
    public String getSmscAddress(int slotId) {
        return null;
    }

    @Override
    public boolean isVendorApkAvailable(String packageName) {
        return false;
    }

    @Override
    public int getCurrentPrimaryCardSlotId() {
        return -1;
    }
}
