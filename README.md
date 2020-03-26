<h1 align="center">Welcome to Corewar_42 👋</h1>
<p>
  <img alt="Version" src="https://img.shields.io/badge/version-1.0-blue.svg?cacheSeconds=2592000" />
  <a href="https://github.com/charlesctr/Corewar_42/subject.pdf" target="_blank">
    <img alt="Documentation" src="https://img.shields.io/badge/documentation-yes-brightgreen.svg" />
  </a>
  <a href="https://github.com/kefranabg/readme-md-generator/graphs/commit-activity" target="_blank">
</p>

<h1>What is Corewar?</h1> 

<p>
  
* Corewar is a very peculiar game. It’s about bringing “players” together around a “virtual machine”, which will load some “champions” who will fight against one an- other with the support of “processes”, with the objective being for these champions to stay “alive”.  
  
* The processes are executed sequentially within the same virtual machine and mem- ory space. They can therefore, among other things, write and rewrite on top of each others so to corrupt one another, force the others to execute instructions that can damage them, try to rewrite on the go the coding equivalent of a Côtes du Rhône 1982 (that is one delicious French wine!), etc...  

* The game ends when all the processes are dead. The winner is the last player reported to be “alive”.   </p>


## Install

```sh
make
```

## Usage

```sh
./corewar [-dump <nb> -n <nb>] file1.cor file2.cor ...
	-dump <nb> : dump memory in hexadecimal after <nb> cycles then quit
	-n : set id of next player. Player_id must > 0 and <= player_nb
	-v : show operations and cycle
	-p : show movement of cursor
  
./asm [-v=verbose] [champion.s]
```

## Run tests

```sh
./script_find_all.sh [path/to/directory/to/.s]
```

## Authors

👤 **Charles Ctr**

* GitHub: [@charlesctr](https://github.com/charlesctr)

👤 **Flhember**

* GitHub: [@therrythecreator](https://github.com/therrythecreator)

👤 **Jleblond**

* GitHub: [@touilleWoman](https://github.com/touilleWoman)

👤 **Naali**

* GitHub: [@Bainhail](https://github.com/Bainhail)

## Show your support

Give a ⭐️ if this project helped you!

## 📝 License

Copyright © 2020 [Charles Ctr] (https://github.com/charlesctr).<br />
***
