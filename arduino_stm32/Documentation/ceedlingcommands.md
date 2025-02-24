# Ceedling Commands

## Initialize Ceedling Project

To initialize a new Ceedling project, use the following command:

```sh
ceedling new <project_name>
```

Replace `<project_name>` with the name of your project.

Example:

```sh
ceedling new my_project
```

This will create a new directory named `my_project` with the necessary files and folders for a Ceedling project.

## Create Test Module

To create a new test module using Ceedling, use the following command:

```sh
ceedling create:test[<module_name>]
```

Replace `<module_name>` with the path of the module you want to create.

Example:

```sh
ceedling create:test[my_module]
```

This will generate a test file for `my_module` in the `test` directory.