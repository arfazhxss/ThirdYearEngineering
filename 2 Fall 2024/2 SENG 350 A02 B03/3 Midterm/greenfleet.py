from abc import ABC, abstractmethod
from typing import List
import time
from datetime import datetime

# Singleton Pattern for Real-time System
class RealTimeSystem:
    _instance = None
    
    def __new__(cls):
        if cls._instance is None:
            print("[System] Creating new RealTimeSystem instance")
            cls._instance = super(RealTimeSystem, cls).__new__(cls)
            cls._instance.active_rides = {}
        return cls._instance
    
    def update_ride_status(self, ride_id: str, status: str):
        print(f"[RealTime] Updating ride {ride_id} status to: {status}")
        self.active_rides[ride_id] = status
        print(f"[RealTime] Current active rides: {self.active_rides}")
    
    def get_ride_status(self, ride_id: str) -> str:
        status = self.active_rides.get(ride_id, "Not Found")
        print(f"[RealTime] Retrieved status for ride {ride_id}: {status}")
        return status

# Builder Pattern for Notifications
class Notification:
    def __init__(self):
        self.title = ""
        self.message = ""
        self.channel = ""
        self.priority = ""
        self.timestamp = ""

    def __str__(self):
        return f"""
[Notification Details]
Title: {self.title}
Message: {self.message}
Channel: {self.channel}
Priority: {self.priority}
Timestamp: {self.timestamp}
"""

class NotificationBuilder:
    def __init__(self):
        self.notification = Notification()
    
    def set_title(self, title: str):
        print(f"[Builder] Setting notification title: {title}")
        self.notification.title = title
        return self
    
    def set_message(self, message: str):
        print(f"[Builder] Setting notification message: {message}")
        self.notification.message = message
        return self
    
    def set_channel(self, channel: str):
        print(f"[Builder] Setting notification channel: {channel}")
        self.notification.channel = channel
        return self
    
    def set_priority(self, priority: str):
        print(f"[Builder] Setting notification priority: {priority}")
        self.notification.priority = priority
        return self
    
    def build(self):
        self.notification.timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        print("[Builder] Building notification...")
        return self.notification

# Demo usage
def main():
    print("\n=== GreenFleet System Demo ===\n")
    
    # Using Singleton Real-time System
    print("[Test] Testing Real-time System (Singleton):")
    rts1 = RealTimeSystem()
    rts2 = RealTimeSystem()
    print(f"[Test] Are instances the same? {rts1 is rts2}")
    
    # Update some ride statuses
    rts1.update_ride_status("RIDE001", "Driver En Route")
    rts1.update_ride_status("RIDE002", "Ride in Progress")
    print(f"[Test] Getting status: {rts2.get_ride_status('RIDE001')}")
    
    print("\n[Test] Testing Notification Builder:")
    # Create a rider notification
    rider_notification = (NotificationBuilder()
        .set_title("Driver Arriving Soon")
        .set_message("Your driver John will arrive in 3 minutes")
        .set_channel("SMS")
        .set_priority("High")
        .build())
    print(rider_notification)
    
    # Create a driver notification
    driver_notification = (NotificationBuilder()
        .set_title("New Ride Request")
        .set_message("Passenger waiting at Downtown Station")
        .set_channel("Push")
        .set_priority("Medium")
        .build())
    print(driver_notification)

if __name__ == "__main__":
    main()
