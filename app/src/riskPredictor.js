
const REST = 'rest';
const WALKING = 'walking';
const RUNNING = 'running';

const FALLING = 1;
const ERRATIC = 2;

const RUNCERTAIN = 0;
const RLOW = 1;
const RMEDIUM = 2;
const RHIGH = 3;


export const predict = (hr, activity, avg_hr, last_activity) => {

    if (activity === ERRATIC) {
        return RUNCERTAIN;
    }

    if (activity === FALLING) {
        if (last_activity === RUNNING || last_activity === FALLING) {
            return RHIGH;
        }
        return RMEDIUM;
    }

    if (activity === REST) {
        const hr_diff = hr / avg_hr;

        if (last_activity === REST) {
            if (hr < 60 || hr > 100 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            if (hr_diff > 1.4) {
                return RHIGH;
            }
        }
        if (last_activity === WALKING) {
            if (hr < 60 || hr > 180|| hr_diff > 1.4) {
                return RHIGH;
            }
            if (hr < 80 || hr > 120 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            return RLOW;
        }
        if (last_activity === RUNNING) {
            if (hr < 60 || hr > 210|| hr_diff > 1.4) {
                return RHIGH;
            }
            if (hr < 80 || hr > 180 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            return RLOW;
        }

        if (hr < 60 || hr > 100 || hr_diff > 1.4) {
            return RMEDIUM;
        }
        return RLOW;
    }

    if (activity === WALKING) {
        console.log("WALKING")
        const hr_diff = hr / avg_hr;

        if (last_activity === REST) {
            console.log("WALKING REST")
            if (hr < 60 || hr > 100 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            if (hr_diff > 1.4) {
                return RHIGH;
            }
        }
        if (last_activity === WALKING) {
            console.log("WALKING WALKING")
            if (hr < 60 || hr > 180 || hr_diff > 1.4) {
                return RHIGH;
            }
            if (hr < 80 || hr > 120 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            return RLOW;
        }
        if (last_activity === RUNNING) {
            console.log("WALKING WALKING")
            if (hr < 60 || hr > 210|| hr_diff > 1.4) {
                return RHIGH;
            }
            if (hr < 80 || hr > 180 || hr_diff < 0.8 || (hr_diff > 1.2 && hr_diff < 1.4)) {
                return RMEDIUM;
            }
            return RLOW;
        }

        if (hr < 60 || hr > 180 || hr_diff > 1.4) {
            return RMEDIUM;
        }
        
        return RLOW;
    }

    if (activity === RUNNING) {

        const hr_diff = hr / avg_hr;

        if (last_activity === REST) {
            if (hr < 60 || hr > 150 || hr_diff < 0.8 || (hr_diff < 0.8 && hr_diff > 1.2)) {
                return RHIGH;
            }
        }
        if (last_activity === WALKING) {
            if (hr < 80 || hr > 120|| hr_diff > 1.4 || hr_diff < 0.8) {
                return RHIGH;
            }
        }
        if (last_activity === RUNNING) {
            if (hr < 60 || hr > 210|| hr_diff > 1.4) {
                return RHIGH;
            }
        }
        if (hr < 60 || hr > 180 || hr_diff > 1.4) {
            return RHIGH;
        }

        return RMEDIUM;
    }

    return RUNCERTAIN;
}