// Top
// units: inches

epsilon = 0.01;

width = 5;
depth = 4.5;
base_thickness = 1/4;

antenna_thickness = 0.4;
antenna_length = 2.40;

notch_height = 1/4;
notch_gap = 1/8;
notch_support = 1/8;

center_height = 3/4;
center_sides = 1;

pole_sides = 1/4;
pole_count = 12;
pole_radius = 2;
pole_height_min = 0.1;
pole_height_max = center_height;

// base
cube([width, depth, base_thickness]);

// notches
notch_sub = 2 * notch_support + notch_gap;
translate([0, 0, -notch_height])
difference() {
    cube([width, depth, notch_height]);
    
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
}

// center
translate([width / 2, depth / 2, base_thickness])
hull() {
    translate([0, 0, center_height / 2])
    cube([center_sides / 2, center_sides / 2, center_height], center = true);
    
    translate([0, 0, epsilon / 2])
    cube([center_sides, center_sides, epsilon], center = true);
}

// circle
translate([width / 2, depth / 2, base_thickness])
for (i=[0:pole_count-1]) {
    height = pole_height_min + (2 * min(i, pole_count - i)) * (pole_height_max - pole_height_min) / pole_count;
    rotate([0, 0, i * 360 / pole_count])
    translate([0, - pole_radius, height / 2])
    hull() {
        translate([0, -pole_sides / 4, 0])
        cube([pole_sides / 2, pole_sides / 2, height], center = true);
        
        translate([0, 0, epsilon / 2 - height / 2])
        cube([pole_sides, pole_sides, epsilon], center = true);
    }
}