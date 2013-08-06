float diffuse = max( dot( normal, lVector ), 0.0);
diffuse *= (0.5 + 0.5 * sin( uScale * vModelPosition.x ) *
                        sin( uScale * vModelPosition.y ) * 
                        sin( uScale * vModelPosition.z ) );