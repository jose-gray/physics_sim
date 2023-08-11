# Physics Simulator

The goal: <br/>
Use TDD and OOP to do fun things


<h1>The physics <br/></h1>
All particles are modelled as smooth (no friction) spheres. Mass and radius can be set <br/><br/>
<h3> Astro mode <br/></h3>
(astro mode is for gravitational attraction between 'planets')<br/>
There is newtonian gravitational attraction between all particles. <a href="https://en.wikipedia.org/wiki/Newton%27s_law_of_universal_gravitation">link</a> <br/>
G can be set (this sets the stregth of the force) <br/>
collisions with each other are optionaly some amount inelastic (i.e some energy is lost) <br/>
if particles collide with insufficient energy to escape each other then they combine to make a bigger planet (conserving mass, momentum, energy and centre of mass) <br/><br/>
<h3> Rocket <br/></h3>
is given gravity from particles<br/>
no collisions </br>
enter resets to (0,0) <br/>
backspace goes to rocket frame or baack <br/>
accleration is added to rocket with arrow keys<br/>
<br/><br/>
<h3> Thermodynamics mode <br/></h3>
collisions with each other are optionaly some amount inelastic (i.e some energy is lost) <br/>
collisions with walls are optionaly some amount inelastic (i.e some energy is lost) <br/>
walls can move <br/>
there is the option for uniform gravity (small scale gravity that is straight downwards like we experiance)<br/>
Pressure and temperature are output <br/>
note because we have a somewhat 2-D world: <br/>
    . P is force per unit length (irl it is force per unit area) <br/>
    . T is based on 2 degrees of freedom for random motion<br/>
    . Ideal gas law becomes PA=NKT <br/><br/>
<h3> Ions mode <br/></h3>
electrostatic coloumbs law between all particles. <a href="https://en.wikipedia.org/wiki/Coulomb%27s_law">link</a> <br/>
4 $\pi$ $\epsilon$<sub>0</sub> = 0.000000001 (this sets the strength of the force)<br/>
all magnetic effects ignored (pretend $\mu$<sub>0</sub> is rlly big)<br/>
collisions with each other are optionaly some amount inelastic (i.e some energy is lost) <br/>
collisions with walls are optionaly some amount inelastic (i.e some energy is lost) <br/><br/>
<h1>TODO list: <br/></h1>
  ✔️ make 2-d particle <br/>
  ✔️add motion <br/>
  ✔️add elastic colisions with walls <br/>
  ✔️(7) add gravity uniform -> next task make tests for this -> test only outputs i.e position <br/>
  ✔️(8) refactor classes and tests - thoughts for this: only outputs of particle get tested, i.e. position, maybe make an update particle class<br/>
  ✔️(9.1) refactors time increment to belong to the particle. <br/>
  ✔️(9.2) tidy up main and display. <br/>
  ✔️(9.3) tidy up tests. <br/>
  ✔️(10) add option to make collsiions some amount inelastic <br/>
  ✔️(11) add more particles in a good way, maybe an array for particle locations <br/>
  ✔️(11.int) bounces between particles <br/>
  ✔️(12) add grvity between particles <br/>
  ✔️(13) add "modes" and improve setup <br/>
  ✔️(14) fix vanishing particles bug <br/>
  ✔️(15) investigate rotation <br/>
  ✔️(16) box size different for different demos <br/>
  ✔️(17) add charged particles interaction <br/>
  ❗  (18) calculate separate to display - eh need help <br/>
  ❗  (19) store already calculated stuff to avoid repetition -ditto <br/>
  ✔️(20) in thermo mode display the temperature <br/>
  ✔️(21) in thermo mode display the pressure on each wall <br/>
  ✔️(22) sig figs!! <br/>
  ✔️(23) way to change volume PA = NKT <br/>
  ✔️(24) sound waves demo <br/>
  ✔️ (25) the big refactor: <br/>
  ....✔️ make everything vectors <br/>
  ....✔️ interactions calculator could do with some helper functions maybe, but kind of a pain to pass everything around, maybe a suggestion to use it's own class? <br/>
  ....✔️ make particles eating each other nicer (mass and radius updated in a nice way) and amny particles demo <br/>
  ✔️ make space rocket <br/>
  .... different looking thing <br/>
  .... responds to arrow keys <br/>
  .... shift + arrow keys boost <br/>
  ✔️ (27) make way to trace particle<br/>
  .... change ref frames <br/>
  :o: (28) bool operator for particles and test tidy<br/>
  :o: (29) be able to click the acclerating particle </br>
  :o: (31) visualise teh fields with colour maybe <br/>
  :o: (32) more refactor <br/>
  ...... a struct for thermo dynamics variables that can get passed to calculators <br/>
  ...... static, const functions etc. <br/>
  ...... std::array rather than passing around size. <br/>
  ...... display seprated into calculate and display <br/> 
  ...... think about where stuff is intilaised <br/>
  ...... time per frame?<br/>
  :o: (32) zoom out <br/>

  
  <h3>random ideas: <br/></h3>
  evolution type stuff, probably involving a new class of 'bacteria' rather than particles<br/>
  more interactivity, pick up and move walls/ particles? <br/>
  give walls some mass <br/>
  car traffic <br/>
  aerodynamics/ particle flow <br/>
  make liquids, surface tension stuffs - water waves <br/>
  atoms? - what model though? <br/>
  
  
<h1>Testing framework: GTest <br/></h1>
<h3>Testing coverage:<br/></h3>
.particle: good <br/>
.LinearMotionCalculator: good <br/>
.wall: good <br/>
.wallCalculator: good <br/>
.ParticleCollisionCalculator: medium <br/>
.Pressure Calculator: good <br/>
.GravityCalculator: medium <br/>
.CoulumbsLawCalculator: medium <br/>
.SigFigsCalculator: good <br/>
.WallCollisionsCalculator: medium good <br/>
.CalculatorManager: nope <br/>
.time: none, relies on the time of day <br/>
.demos: none, doesn't feel necessary, more of an output <br/> 
.display: none, basically uses raylib <br/>
