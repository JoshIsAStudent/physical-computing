import os
import re

unresolvedComments = 0
commentRegex = r"\[(.*?)\][><]\[(.*?)\]"
root = "../post-content"
experiments = os.listdir(root)

for experiment in experiments:
    with open(root + "/" + experiment + "/README.md") as originalFile:

        # GET CONTENT #
        originalContent = originalFile.read()
        post = originalContent

        # OUTPUT COMMENT INFO #
        comments = [comment for comment in re.finditer(commentRegex, originalContent)]
        if len(comments) > 0:
            print(experiment + " has " + str(len(comments)) + " unresolved comments")
            unresolvedComments = unresolvedComments + len(comments)

        # GENERATE OUTPUT #
        # post = re.sub(r"^# .+\n", "", post) # Remove level one headers
        post = re.sub(r"\n#(#+) ", r"\n\1 ", post) # Reduce level of headers
        post = re.sub(commentRegex, r"\1", post) # Strip out comments

        # Include kit info
        post = post.replace(
            "# Components Used",
            "# Components Used\n"\
            "This experiment uses the Arduino UNO R3 Project Starter Kit."
        )

        # Include standard components
        post = post.replace(
            "?[standard-components]",
            "* 1 x UNO R3 Controller Board (the Arduino)\n"\
            "* 1 x Breadboard\n"\
            "* Breadboard jumper wires"
        )

        # Make image links route directly to github
        post = re.sub(
            r"!\[(.*?)\]\((.*?)\)",
            r"![\1](https://raw.githubusercontent.com/JoshIsAStudent/physical-computing/main/post-content/" + experiment + r"/\2)",
            post
        )

        # Complete code template
        # post = re.sub(
        #     r"\?\[complete-code\]\((.+?)\)",
        #     "You can see the complete code on [GitHub](https://github.com/JoshIsAStudent/physical-computing/tree/main/post-content/" + experiment + "/\\1).",
        #     post
        # )

        # Youtube video template
        # post = re.sub(
        #     r"\?\[youtube-video\]\((.+?)\)",
        #     "See a demo on [YouTube](https://youtu.be/\\1).",
        #     post
        # )
        post = re.sub(
            r"\?\[youtube-video\]\((.+?)\)",
            '<iframe width="560" height="315" src="https://www.youtube.com/embed/\\1" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>',
            post
        )

        # Tidy new lines
        post = re.sub("\n\n\n+", "\n\n", post)

        # Save output
        with open("posts/" + experiment + ".md", "w") as outputFile:
            outputFile.write(post)

if unresolvedComments > 0:
    print()
    print("There are " + str(unresolvedComments) + " unresolved comments in total")
