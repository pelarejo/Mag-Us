[33mcommit 7cdf92684312389a9100f9456f660af753dbf0af[m
Author: Crunch-Hudson <benjamin.virgo@epitech.eu>
Date:   Mon Feb 2 18:59:10 2015 +0100

    Leap Motion
    
    Ajout de la detection de mouvement qui fonctionne enfin !

[33mcommit 45921c5e3d2e24265416d385271365e5ad71aece[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Mon Feb 2 18:27:57 2015 +0100

    Important commit - Added working leapmotion integration in MyCharacter

[33mcommit 94106d563edc51d32930958fa26bab2018632e6a[m
Author: Crunch-Hudson <benjamin.virgo@epitech.eu>
Date:   Wed Jan 28 15:41:36 2015 +0100

    Revert "Commit de la detection de mouvement"
    
    This reverts commit 4df5c1e37bd41db259e0c9a712e89e1bc0cb834b.

[33mcommit 4df5c1e37bd41db259e0c9a712e89e1bc0cb834b[m
Author: Crunch-Hudson <benjamin.virgo@epitech.eu>
Date:   Wed Jan 28 14:31:16 2015 +0100

    Commit de la detection de mouvement

[33mcommit a8a06f21c9fc953c9b86106ca0a2dae073083f90[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 27 18:51:45 2015 +0100

    Merged .gitignore with leap-ue4 .gitignore

[33mcommit b3e71113996e5a7455c83143f34cd69af39b8f80[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 27 18:49:27 2015 +0100

    Added  necessary Binaries/*.dll for leap-ue4

[33mcommit f87fe13f10c83ae6dd4b809dc8e35679a8564879[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 27 18:48:18 2015 +0100

    Added Plugins/ leap-ue4

[33mcommit 2d38734e4cd45ad24a76a5b22a748684babfa4d7[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 27 18:47:50 2015 +0100

    Added leap-ue4 content

[33mcommit f07af8c222fff245d9e5c450066a4d1c8bc10ec6[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 27 18:19:04 2015 +0100

    Revert "ADD LEAPMOTION"
    Reverting commit because it creates conflicts
    This reverts commit 02aa741b4d6ff03dd7cc6dd2ededdcc159805a14.

[33mcommit 02aa741b4d6ff03dd7cc6dd2ededdcc159805a14[m
Author: Crunch-Hudson <benjamin.virgo@epitech.eu>
Date:   Tue Jan 27 17:28:00 2015 +0100

    ADD LEAPMOTION
    
    Ajout du LeapMotion Plugin ainsi que le BP associé au catching des event
    gesture

[33mcommit 4f2de906ccab7c06bda6059330c7b0feedb6169b[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Mon Jan 26 22:34:56 2015 +0100

    Added link to README.md

[33mcommit 2065724622aa275d9856a5dc8740c60380f69bc3[m
Author: loverg-c <clement.lovergne@epitech.eu>
Date:   Mon Jan 26 16:31:35 2015 +0100

    Graphic asset : Cube/Sphere/MultiColor Texture/HUD

[33mcommit d544c67146fa0ba6899721cde478e9882d6842c6[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 26 11:02:41 2015 +0100

    LockOn V2 - Way more precise + lose lockon on distance + Changed Lockon distance in BP

[33mcommit 31c6e6ecd80a2fefe3dc564c89a28e0b0c92e0e0[m
Author: Remi Lesaffre <remi.lesaffre@epitech.eu>
Date:   Mon Jan 26 10:20:12 2015 +0100

    Ajout de commentaires dans MagUsCharacter pour le set de l'instigator. Impulsion du projectile retirée si collision avec ennemi (laissée pour les autres collisions). Fix du modèle qui part en couille au démarage

[33mcommit 1f5583122c75ec161a438a58579214eaebb26459[m
Author: Remi Lesaffre <remi.lesaffre@epitech.eu>
Date:   Thu Jan 22 18:33:24 2015 +0100

    Ajout de la gestion de la physique et collision sur le AICharacter_BP (Faudra régler le fait que sa physique parte en couille). Ajout de la gestion des dégats sur le MagUsAICharacter

[33mcommit fba377ab79905601ab53139f93d2e5a2385aa75b[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Wed Jan 21 22:20:17 2015 +0100

    Locking system stops when ennemy leaves the screen

[33mcommit deabda8977244cba52cb966881b3ceb24fd1a850[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Wed Jan 21 18:18:47 2015 +0100

    Hidden AI lock beta

[33mcommit a557e9ab037883f740c118683bacd7d9780cc266[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Wed Jan 21 11:05:03 2015 +0100

    Added authors to README

[33mcommit ab56a78bb5c87a402e700bbbe19f11c2bfb4cba3[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Wed Jan 21 10:32:09 2015 +0100

    Fucking UE not asking for BP saving when reparenting. This commit repairs previous broken commit. Repairs: AICharacter_BP.uasset - Example_Map.uasset

[33mcommit 4d622751019bb5bb1a137da1665a461784131057[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 20 20:30:40 2015 +0100

    This commit essentialy erases all changes done in the previous commit. This is the good one

[33mcommit ebba03751288e9efb533d7a81e1d048cc59c8b9a[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 20 19:34:59 2015 +0100

    Centered MotionlessAI and added Target for future MotionAI

[33mcommit 34703c0b48efaa5d2ae9b610bc6815acb61b0946[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 20 19:26:35 2015 +0100

    Changed Enemy related content to AI class structure with UE Naming convention

[33mcommit 6159c61040985469de800830374485372a9f8404[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 20 19:13:20 2015 +0100

    Lock system finished

[33mcommit a1623dcb7402ac1ece7f875b8ea5c61c11032c6f[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 19 20:43:38 2015 +0100

    Added possibility of changing crosshair position in HUD

[33mcommit 6c8ded589c62e0e47b900c6ac966adb5f57d5a46[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 19 20:08:17 2015 +0100

    renamed crosshiar to crosshair in HUD cpp file

[33mcommit d229ebd6629954f7f3c3329d89a05f24a1190fd2[m
Merge: d4cbcce aad77dd
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 19 19:55:13 2015 +0100

    Merge branch 'master' of github.com:Py0s/Mag-Us into lockon

[33mcommit d4cbcce6d27a5999fca8429665a116a034d5defd[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 19 19:54:36 2015 +0100

    Finding enemy to lock

[33mcommit aad77dd173dd4646c39489b6ed989ba531810594[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Mon Jan 19 19:29:02 2015 +0100

    Added link to README.md
    
    https://docs.unrealengine.com/latest/INT/Programming/Development/CodingStandard/index.html

[33mcommit 32170a8394e14a9a274f1c41e67751366ce3c2d0[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Mon Jan 19 16:35:45 2015 +0100

    BP implementation of raytrace

[33mcommit 2f9275abf24d9fb520dfcfd3b1f1cea3b36a360f[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Mon Jan 19 11:19:41 2015 +0100

    Enemy BP added. Only need to implement true raytracing

[33mcommit b5fcd29eacbdb6e4f9f1dfb817c130e61d00be22[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Wed Jan 14 20:26:22 2015 +0100

    Unfinished enemy_bp creation

[33mcommit 03a61bbb5bd55ed8e9642030eec1757b4e48be76[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Wed Jan 14 20:25:37 2015 +0100

    Update Setting up azerty with file import

[33mcommit afca82c6b65b7176ee920a39052e585d432f0db6[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Wed Jan 14 15:07:18 2015 +0100

    Default keyboard shortcut with azerty viewport

[33mcommit b2eeaf8633c87e6b7f16631d29fc21590d048913[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Wed Jan 14 14:10:03 2015 +0100

    Added Animation starter pack + added ennemy on map

[33mcommit 35e53c0cd3d4f437877a5c01d572904c5361af50[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Tue Jan 13 13:11:49 2015 +0100

    Update "Installing Environment" chapter to README.md

[33mcommit 6633f2ecc1a6c613952e2b9a8987f250b9b454b9[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 13 13:03:23 2015 +0100

    ignored *.opensln, *.sln and *.sdf

[33mcommit 132e4148b1f133c84c8b39370a62f8b2b585573d[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 13 13:02:55 2015 +0100

    deleted Visual Studio *.sdf *.sln

[33mcommit 9191d29c9958f0ed6fdff11c8d9d3bdbb926e918[m
Author: Pelayo <parejo_p@epitech.eu>
Date:   Tue Jan 13 12:38:20 2015 +0100

    AZERTY support in game

[33mcommit 127eac043adbdbc46b15d9d29603acef2fab6737[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Tue Jan 13 12:26:37 2015 +0100

    Added simple instruction for devs to get started !

[33mcommit 7c061848ad879c72c3bc694bf66f818328330b9b[m
Author: PAREJO PAGADOR Pelayo <pelayo.parejopagador@epitech.eu>
Date:   Mon Jan 12 21:35:05 2015 +0100

    Initial commit + .gitignore updated for VS and UE

[33mcommit a0a6eaa4b0343ec3d228ab5db0e0a39e78c0fe5e[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Mon Jan 12 19:56:47 2015 +0100

    Update README.md

[33mcommit 42f1855a9128c28b26474f554cf18807fbe60b9f[m
Author: Pelayo PAREJO PAGADOR <Py0s@users.noreply.github.com>
Date:   Mon Jan 12 19:56:11 2015 +0100

    Initial commit
