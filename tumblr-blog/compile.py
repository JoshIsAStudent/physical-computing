import os
import re

unresolvedComments = 0;
commentRegex = r"\[([^\[\]]*)\]>\[([^\[\]]*)\]";
experiments = filter(lambda x: re.search("^\d\d-.+$", x), os.listdir(".."))

for experiment in experiments:
    with open("../" + experiment + "/README.md") as originalFile:

        # GET CONTENT #
        originalContent = originalFile.read()
        post = originalContent

        # GENERATE TITLE #
        title = "Experiment " + experiment.title().replace("-"," ")

        # OUTPUT COMMENT INFO #
        comments = [comment for comment in re.finditer(commentRegex, originalContent)];
        if len(comments) > 0:
            print(experiment + " has " + str(len(comments)) + " unresolved comments")
            unresolvedComments = unresolvedComments + len(comments)

        # GENERATE OUTPUT #
        post = re.sub(r"^# .+\n", "", post) # Remove level one headers
        post = re.sub(r"\n#(#+) ", r"\n\1 ", post) # Reduce level of headers
        post = re.sub(commentRegex, r"\1", post) # Strip out comments
        post = "# " + title + "\n" + post # Prepend title (to be moved into title field when posted to tumblr)

        # Include kit info
        post = post.replace(
            "# Components",
            "# Components\n"\
            "This experiment uses the Arduino UNO R3 Project Starter Kit."
        )

        # Include standard components
        post = post.replace(
            "@standard-components",
            "* 1 x UNO R3 Controller Board (the Arduino)\n"\
            "* 1 x Breadboard\n"\
            "* Breadboard jumper wires"
        )

        # Make image links route directly to github
        post = re.sub(
            r"!\[(.*?)\]\((.*?)\)",
            r"![\1](https://github.com/JoshIsAStudent/physical-computing/blob/main/" + experiment + r"/\2)",
            post
        )

        # Complete code template
        post = post.replace(
            "@complete-code",
            "You can see the complete code on [GitHub](https://github.com/JoshIsAStudent/physical-computing/blob/main/" + experiment + "/" + experiment + ".ino)."
        )

        # Tidy new lines
        post = re.sub("\n\n\n+", "\n\n", post)

        with open("posts/" + title + ".md", "w") as outputFile:
            outputFile.write(post)

if unresolvedComments > 0:
    print()
    print("There are " + str(unresolvedComments) + " unresolved comments in total")
