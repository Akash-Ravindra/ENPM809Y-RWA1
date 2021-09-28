/**
 * @file main.cpp
 * @author Akash Ravindra (aravind2@umd.edu)
 * @brief RWA1 - A part sorting algorithm
 * @details Based on user inputs such as the number of boxes, number of parts
 * per box and the number of parts to sort, this algorithm generates the
 * distribution based on a set rules. No box can be half full. No small box can
 * have a per box count greater than a bigger box. Not all parts needs to be
 * sorted ( Mathematically impossible based on certain inputs )
 * @version 0.1
 * @date 2021-09-26
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <string>
// using namespace std;

/**
 * @brief User defined data object that contains information about each type of
 * box
 * @details This datatype acts as a container to hold all the attributes
 * associated with a box meant for the sorting algo. box_metadata.no_boxes and
 * box_metadata.no_items_perbox are user inputs.
 */
struct box_metadata {

  unsigned int no_boxes{}; /**<Contains the number of boxes of this
                  type.Obtained from the user as an input*/

  unsigned int no_items_perbox{}; /**<Contains the number of parts each box of
                 this type can hold. Obtained from the user as an input*/

  unsigned int no_free_boxes{}; /**<Contains the number of boxes that are free
                   and can be filled with parts. This is init with the
                   no_boxes and during runtime based on the number of
                   parts sorted its value changes*/

  box_metadata *next_fill_box{}; /**<Contains the address of the box that parts
                        can be sorted into next.*/

  std::string print_stat{}; /**<Contains the text that is associated with this
                   Box that needs to be used when displaying the
                   results to the user*/
};

/**
 * @brief User defined data object that holds box metadata and the number of
 * parts that remain to be sorted
 * @details This struct acts as a single point of data manipulation for the
 * algo. It contains the list of all the box_metadata strct or each type of box
 * with their initial values. part_sorting_list.currentbox is a pointer that
 * always points to the box that parts need to be sorted into. If the pointer
 * ends up being a NULL then we have reached the end of the list
 */
struct part_sorting_list {
  box_metadata box_XL{.next_fill_box{&box_L}, .print_stat{"XL box "}}; /**<A
                      box_metadata stuct to store the data for the XL box*/
  box_metadata box_L{
      .next_fill_box{&box_M},
      .print_stat{
          "L box "}}; /**<A box_metadata stuct to store the data for the L box*/
  box_metadata box_M{
      .next_fill_box{&box_S},
      .print_stat{
          "M box "}}; /**<A box_metadata stuct to store the data for the M box*/
  box_metadata box_S{.print_stat{
      "S box "}}; /**<A box_metadata stuct to store the data for the S box*/
  box_metadata *current_box{&box_XL}; /**<A pointer that always points to the
box that parts needs to be sorted into. If the pointer ends up becoming a NULL
then there are no more boxs left to sort into*/
  unsigned int number_parts_left{};   /**<The number of parts that need to be
               sorted at any    given time. Obtained as an user input.
               Its    value decreases as the    parts get sored*/
};

void get_total_parts(part_sorting_list &);
void get_total_boxes(part_sorting_list &);
void get_parts_per_box(part_sorting_list &);
void fill_up_boxes(part_sorting_list &);

bool positive_int_check(char const &s) {}
/**
 * @brief Get the total parts object
 * @details The user is prompted to enter the total number of parts that needs
 * to be sorted into the boxes. Validation is carried out on the input to insure
 * that the number entered by the user is a positive integer.
 * @param tempPSLA part_sorting_list passed as a reference to store the inputs
 * given by the user into the part_sorting_list.number_parts_left of each type
 * of box in the list
 */
void get_total_parts(part_sorting_list &tempPSL) {
    while (std::cout << "How many parts in total? " &&
           (!(std::cin >> tempPSL.number_parts_left) ||
            tempPSL.number_parts_left < 0)) {
      std::cout << "Not a positive int \n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  
//   std::string input{};
//   int result;
//   do {
//     result = 0;
//     std::cout << "How many parts in total? ";
//     std::getline(std::cin >> std::ws, input);
//     for (char &c : input) {
//       if (!isdigit(c)) {
//         result = 1;
//         std::cout << "Input not a positive integer\n";
//       }
//     }
//   } while (result);
//   std::string::size_type sz;
//   tempPSL.number_parts_left = std::stoi(input, &sz);

  /////////////////////// For Debugging///////////////////////////////////////
  // std::cout<<"The numbe you entered was : "<<tempPSL.number_parts_left;
  ////////////////////////////////////////////////////////////////////////////
}

/**
 * @brief Get the total boxes object
 * @details The user is pormpted to input the number of boxes of S, M, L and XL
 * respectively. Input validation is carried out to make sure that the number
 * entered is a positive integer
 *
 * @param tempPSL A part_sorting_list passed as a reference to store the inputs
 * given by the user into the box_metadata.no_boxes of each type of box in the
 * list
 */
void get_total_boxes(part_sorting_list &tempPSL) {
  while (std::cout << "How many boxes for S/M/L/XL? " &&
         (!(std::cin >> tempPSL.box_S.no_boxes >> tempPSL.box_M.no_boxes >>
            tempPSL.box_L.no_boxes >> tempPSL.box_XL.no_boxes) ||
          tempPSL.box_XL.no_boxes < 0 || tempPSL.box_L.no_boxes < 0 ||
          tempPSL.box_M.no_boxes < 0 || tempPSL.box_S.no_boxes < 0)) {
    std::cout << "Not a positive int \n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  ////////////////////////For Debugging  //////////////////////////////////////
  // std::cout<<"The numbe you entered was : "<<tempPSL.box_XL.no_boxes<<"
  // "<<tempPSL.box_L.no_boxes<<" "<<tempPSL.box_M.no_boxes<<"
  // "<<tempPSL.box_S.no_boxes;
  ////////////////////////////////////////////////////////////////////////////
}

/**
 * @brief Get the parts per box object
 * @details The user is prompted to input the number off items that can be held
 * in each kind of box; S, M, L and XL respectively. Input validation is carried
 * out to insure that all the inputs are positive integers and that the value of
 * S < value of M < value of L < value of XL
 * @param tempPSL A part_sorting_list passed as a reference to store the inputs
 * given by the user into the box_metadata.no_items_perbox of each type of box
 * in the list
 */
void get_parts_per_box(part_sorting_list &tempPSL) {
  do {
    while (std::cout << "How many parts per box for S/M/L/XL? " &&
           (!(std::cin >> tempPSL.box_S.no_items_perbox >>
              tempPSL.box_M.no_items_perbox >> tempPSL.box_L.no_items_perbox >>
              tempPSL.box_XL.no_items_perbox) ||
            tempPSL.box_XL.no_items_perbox < 0 ||
            tempPSL.box_L.no_items_perbox < 0 ||
            tempPSL.box_M.no_items_perbox < 0 ||
            tempPSL.box_S.no_items_perbox < 0)) {
      std::cout << "Not a positive int \n";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  } while (!(tempPSL.box_S.no_items_perbox < tempPSL.box_M.no_items_perbox &&
             tempPSL.box_M.no_items_perbox < tempPSL.box_L.no_items_perbox &&
             tempPSL.box_L.no_items_perbox < tempPSL.box_XL.no_items_perbox));
}

/**
 * @brief Fills up the boxes based on the criteria
 * @details After the user has entered all the data, this function recursively
 * goes box by box and attempts to fill it up. If it succeds to do so then the
 * number_parts_left is reduce and it moves on to the next box in the series.
 *
 * @param tempPSL A part_sorting_list passed as a reference to use the inputs
 * given by the user into the box_metadata of each type of box in the list
 */
void fill_up_boxes(part_sorting_list &tempPSL) {
  // Prints the Main heading msg only once
  static int print_once = 1;
  if (print_once) {
    std::cout << "\nBoxes that can be built with " << tempPSL.number_parts_left
              << " pegs:\n-------------------------------------------------\n";
    print_once = 0;
  }
  // Stores the number of free boxes, which initally is equal to the number of
  // boxes
  tempPSL.current_box->no_free_boxes = tempPSL.current_box->no_boxes;
  if (tempPSL.current_box !=
      NULL) { // Makes sure there is a box to sort parts into
    if (tempPSL.current_box->no_free_boxes > 0 &&
        tempPSL.number_parts_left >
            0) { // check if there any parts and boxes left to sort into
      unsigned int possible_parts =
          tempPSL.number_parts_left / tempPSL.current_box->no_items_perbox;
      if (possible_parts >
          0) { // If an integral number of parts could be sorted then, proceed
        // to figure out how many full boxes can be filled
        tempPSL.current_box->no_free_boxes =
            int(tempPSL.current_box->no_boxes - possible_parts) > 0
                ? tempPSL.current_box->no_boxes - possible_parts
                : 0;
        tempPSL.number_parts_left -= (tempPSL.current_box->no_boxes -
                                      tempPSL.current_box->no_free_boxes) *
                                     tempPSL.current_box->no_items_perbox;
      }
    }
    std::cout << tempPSL.current_box->print_stat << "( "
              << tempPSL.current_box->no_boxes << " X "
              << tempPSL.current_box->no_items_perbox << " max): "
              << (tempPSL.current_box->no_boxes -
                  tempPSL.current_box->no_free_boxes)
              << " -- remaining parts: " << tempPSL.number_parts_left
              << "\n"; // Print the Box data
    if (tempPSL.current_box->next_fill_box != NULL) {
      tempPSL.current_box = tempPSL.current_box->next_fill_box;
      fill_up_boxes(tempPSL);
    } else { // If there is no currentbox, this impliess that we have exhuasted
      // all the boxes in the list and we have to display the parts we
      // have remaining
      std::cout << "parts not in boxes: " << tempPSL.number_parts_left << "\n";
    }
  }
}

/**
 * @brief A program to sort the given number of parts in a list of box based on
 * a set of rules
 *
 * @return int
 */
int main() {
  part_sorting_list PSL;
  get_total_parts(PSL);
  get_total_boxes(PSL);
  get_parts_per_box(PSL);
  fill_up_boxes(PSL);
}