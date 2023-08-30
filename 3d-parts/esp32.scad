$fn= $preview ? 32 : 256;
esp_x = 56;
esp_y = 28;
esp_z = 14;
esp_inner_pin_y = 20;
esp_inner_pin_z = 6;
wall_thickness = 2;
d_max = 41;
h_max = esp_x + 2* wall_thickness;
space = 1;

//sizeTest();

translate([1.2*d_max, 0, 0]) lid();

// union() {
//     outerCylinder();
//     translate([(esp_y + 2* space)/-2, d_max/2 - 2*wall_thickness - 5, wall_thickness]) espClip();
// }

module espClip() {
    cube([esp_y + 2* space, wall_thickness, esp_x - wall_thickness]);
    translate([(esp_y - esp_inner_pin_y)/2 + space, (esp_inner_pin_z + 2* wall_thickness) * -1, 0]) cube([esp_inner_pin_y, wall_thickness*2, esp_x - wall_thickness]);
    translate([esp_y/2 + space -wall_thickness, (esp_inner_pin_z + 4* wall_thickness) * -1, 0]) cube([wall_thickness*2, wall_thickness*2, esp_x - 2*wall_thickness]);
}

module outerCylinder() {
    difference() {
        cylinder(h=h_max, d=d_max);
        translate([0, 0, wall_thickness]) cylinder(h=h_max - wall_thickness , d=d_max - 2* wall_thickness);
        translate([0, d_max / -4, 0]) cylinder(h=wall_thickness+space, d=6); // cable hole
    }
}

module lid() {
    difference() {
        cylinder(h=3*wall_thickness, d=d_max+2*wall_thickness);
        translate ([0,0,wall_thickness]) union() {
            difference() {
                cylinder(h=2*wall_thickness, d=d_max+0.1);
                cylinder(h=2*wall_thickness, d=d_max-2*wall_thickness-0.1);
            } 
            cylinder(h=2*wall_thickness, d=d_max-4*wall_thickness);
        }        
    }
}

module sizeTest() {
    difference() {
        cylinder(h=3*wall_thickness,d=d_max-1);
        cylinder(h=3*wall_thickness,d=d_max-3*wall_thickness-1);
    }
    translate([1.1*d_max,0,0]) difference() {
        cylinder(h=3*wall_thickness,d=d_max);
        cylinder(h=3*wall_thickness,d=d_max-3*wall_thickness);
    }
    translate([2.2*d_max,0,0]) difference() {
        cylinder(h=3*wall_thickness,d=d_max+1);
        cylinder(h=3*wall_thickness,d=d_max-3*wall_thickness+1);
    }
}