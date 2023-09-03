$fn= $preview ? 32 : 128;
ps_x = 163;
ps_y = 42;
ps_z = 38;

strain_relief_x = 10;
strain_relief_y = 15;
strain_relief_z = 10;
strain_relief_wall = 2;
cable_diam = 5;

screw_diam=3;
screw_z=5;
screw_thread_diam=4.5;
screw_thread_z = 4;
screw_thread_wall = 2;

toggle_x = 13;
toggle_y = 19.5;
toggle_z = 22;

x_max = 220;

wall_thickness = 2;
space = 3;

holder_wall = 4;
holder_clip_diam = 22;
holder_z = 30;

psBox();
translate([1.5*ps_y, 0, 0]) psboxLid();
translate([3.1*ps_y, 0, 0]) psBoxHolder();


module psboxLid() {
    lid_space = 0.1;
    difference() {
        cube([ps_y+2*space+4*wall_thickness, x_max+2*space+4*wall_thickness,2*wall_thickness]);
        difference() {
            translate([wall_thickness - lid_space,wall_thickness - lid_space,wall_thickness]) cube([ps_y+2*space+2*wall_thickness+2*lid_space, x_max+2*space+2*wall_thickness+2*lid_space,wall_thickness]);
            translate([2*wall_thickness + lid_space,2*wall_thickness + lid_space,wall_thickness]) cube([ps_y+2*space-2*lid_space, x_max+2*space-2*lid_space,wall_thickness]);
        }
        translate([3*wall_thickness,3*wall_thickness,wall_thickness]) cube([ps_y + wall_thickness, x_max + wall_thickness,wall_thickness]);
        translate([ps_y - 10,15,0]) cube([toggle_x, toggle_y,toggle_z]);
    }
}

module psBox() {
    difference() {
        union() {
            difference() {
                cube([ps_y+2*space+2*wall_thickness, x_max+2*space+2*wall_thickness,ps_z + space + wall_thickness]);
                translate([wall_thickness, wall_thickness, wall_thickness]) cube([ps_y+2*space, x_max+2*space,ps_z + space]);
            }
            translate([(ps_y+2*wall_thickness+2*space)-(strain_relief_y+2*strain_relief_wall),wall_thickness,wall_thickness]) cableHole();
            translate([0,x_max+wall_thickness+2*space,wall_thickness]) mirror([0,1,0]) cableHole();

            // 4mm distance for screwhole in pc
            ps_screw_posx = wall_thickness + (screw_thread_diam+screw_thread_wall)/2 + 4; 
            ps_screw_posy = (x_max+wall_thickness+space)-(strain_relief_x+screw_thread_wall) - 5 - 4; // 5 is arbitrary distance

            translate([ps_screw_posx, ps_screw_posy, wall_thickness]) pcScrewThread();
            translate([ps_screw_posx+ps_y-2*4, ps_screw_posy-(ps_x-2*4), wall_thickness]) pcScrewThread();
        }
        translate([(ps_y+2*wall_thickness+2*space)-(strain_relief_y+2*strain_relief_wall)/2,wall_thickness,3*wall_thickness]) rotate([90,0,0]) cylinder(h=wall_thickness, d=cable_diam);
        translate([(strain_relief_y+2*strain_relief_wall)/2,x_max+wall_thickness+2*space+wall_thickness,3*wall_thickness]) rotate([90,0,0]) cylinder(h=wall_thickness, d=cable_diam);
    }
}

module cableHole() {
    difference() {
        cube([strain_relief_y + 2*strain_relief_wall, strain_relief_x + strain_relief_wall, strain_relief_z]);
        translate([strain_relief_wall,0,0])cube([strain_relief_y,strain_relief_x,strain_relief_z]);
        translate([-1, strain_relief_x/2, strain_relief_z/2]) rotate([0,90,0]) cylinder(h=strain_relief_y+2*strain_relief_wall+2, d=cable_diam);
    }
}

module pcScrewThread() {
    difference() {
        cylinder(h=screw_z+1, d=screw_thread_diam+2*screw_thread_wall);
        translate([0,0,1]) cylinder(h=screw_z, d=screw_thread_diam);
    }
}

module psBoxHolder () {
    holder_x = ps_y + 2* space + 4*wall_thickness;
    holder_y = ps_z + space + 2*wall_thickness;    
    holder_rail_z = 5;
    holder_rail_x = 3*wall_thickness;

    union() {
        difference() {
            cube([holder_x + 2*holder_wall, holder_y + 2*holder_wall, holder_z + holder_wall]);
            translate([holder_wall, holder_wall, holder_wall]) cube([holder_x, holder_y, holder_z]);
            translate ([(holder_wall+holder_rail_z)*2, holder_wall+holder_rail_z, 0]) cube([(holder_x + 2*holder_wall)-(holder_wall+holder_rail_z)*4, (holder_y + 2*holder_wall)-(holder_wall+holder_rail_z)*2, holder_wall]);
        }

        translate([holder_wall, holder_wall+2*wall_thickness, holder_wall]) cube([holder_rail_x, holder_y - 2*wall_thickness, holder_rail_z]);
        translate([holder_x+holder_wall-holder_rail_x, holder_wall+2*wall_thickness, holder_wall]) cube([holder_rail_x, holder_y - 2*wall_thickness, holder_rail_z]);
        
        translate([0,holder_y+2*holder_wall,0])cube([holder_x+2*holder_wall,holder_wall,holder_z+holder_wall]);
        translate([(holder_clip_diam+2*holder_wall)/2+(holder_x-holder_clip_diam)/2,holder_y+3*holder_wall+holder_clip_diam/2,0]) psBoxHolderClip();
    }


}

module psBoxHolderClip() {
    holder_clip_x = holder_clip_diam+2*holder_wall;
    holder_clip_z = holder_z + holder_wall;
    difference() {
        hull() {
            cylinder(h=holder_clip_z, d=holder_clip_x);
            translate([holder_clip_x/-2,holder_clip_x/-2,0]) cube([holder_clip_x, holder_wall, holder_clip_z]);
        }
        cylinder(h=holder_clip_z, d=holder_clip_diam);
        rotate([0,0,45]) cube([holder_clip_z,holder_clip_z,holder_clip_z]);
    }
}
