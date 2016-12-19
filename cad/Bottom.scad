// Bottom
// units: inches

epsilon = 0.1;

width = 5;
depth = 4.5;
base_thickness = 1/6;

antenna_thickness = 0.4;
antenna_length = 2.40;

notch_height = 1/2;
notch_gap = 1/8;
notch_support = 1/8;
notch_width = 3/4;

// base
translate([0, 0, -base_thickness])
cube([width, depth, base_thickness]);

// notches
notch_sub = 2 * notch_support + notch_gap;
difference() {
    difference() {
        cube([width, depth, notch_height]);
        
        translate([notch_sub, notch_sub, -epsilon])
        cube([width - 2 * notch_sub, depth - 2 * notch_sub, notch_height + 2 * epsilon]);
    }
    
    // 4 cuts
    union() {
        translate([notch_sub, notch_support, -epsilon])
        cube([width - 2 * notch_sub, notch_gap, notch_height + 2 * epsilon]);
        
        translate([notch_sub, depth - notch_sub + notch_support, -epsilon])
        cube([width - 2 * notch_sub, notch_gap, notch_height + 2 * epsilon]);
        
        translate([notch_support, notch_sub, -epsilon])
        cube([notch_gap, depth - 2 * notch_sub, notch_height + 2 * epsilon]);
        
        translate([width - notch_sub + notch_support, notch_sub, -epsilon])
        cube([notch_gap, depth - 2 * notch_sub, notch_height + 2 * epsilon]);
    }
    
    // 2 big cuts
    union() {
        translate([notch_sub + notch_width, -epsilon, -epsilon])
        cube([width - 2 * notch_sub - 2 * notch_width, depth + 2 * epsilon, notch_height + 2 * epsilon]);
        
        translate([-epsilon, notch_sub + notch_width, -epsilon])
        cube([width + 2 * epsilon, depth - 2 * notch_sub - 2 * notch_width, notch_height + 2 * epsilon]);
    }
}

// antenna holder
translate([notch_sub, depth - notch_sub - antenna_thickness - notch_support])
cube([antenna_length, notch_support, notch_height]);