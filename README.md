<p align="center">
  <img src="https://github.com/BaBreton/42-Get_next_line/assets/124448529/43a36b92-4c44-4c58-b03c-b18903712b45" alt="BaBreton" />
</p>
<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue" alt="language" />
  <img src="https://img.shields.io/badge/Mark-100/100-green" alt="language" />
</p>

# 42-Minishell

Minishell is a 42 school project that involves reimplementing a "mini" bash terminal. In this project, I've re-implemented the following built-in functions:

* 'echo' (with '-n' option)
* 'cd' (with relative or absolute path)
* 'pwd' (without options)
* 'export' (without options)
* 'unset' (without options)
* 'env' (without options or arguments)
* 'exit' (without options)



I've also had to reimplement the following features :

* Redirections (in and out to a file)
* Multi commands with pipes
* Manage the environment variables : you can use the '$' with 'echo' or in your redirections to print environment variables.
* Handling signals : 'ctrl-c' and 'ctrl-d'

## Installation 

To create the executable, navigate to the root folder of the project and use the following command:

```bash
  make
```

Then, you can run the program with:

```bash
  ./minishell
```

## Usage

Now that you are in the program, you can enter various bash commands !

<div style="display:flex; justify-content:center; align="center">
  <img src="https://github.com/BaBreton/42-Minishell/assets/124448529/5577b22d-7daa-4330-af86-0a05d3451e37" width="300px" style="margin:5px;">
  <img src="https://github.com/BaBreton/42-Minishell/assets/124448529/51364197-0e89-4142-b0a0-6218c64da257" width="300px" style="margin:5px;">
  <img src="https://github.com/BaBreton/42-Minishell/assets/124448529/d8fad4a1-7322-4f63-9c6d-a2de341d0db7" width="300px" style="margin:5px;">
</div>
